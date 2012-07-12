//
// Kiwi.cc — Kiwi-LibNode
// today is 7/12/12, it is now 01:25 AM
// created by TotenDev
// see LICENSE for details.
//


#define BUILDING_NODE_EXTENSION
#include <cstring>
#include <string>
#include <v8.h>
#include <node.h>
#include <sys/ipc.h> 
#include <sys/msg.h>
//Definitions
#define MaxMsgBuffer 4096
#define	RERROR scope.Close(Boolean::New(false))
#define	RSUCCESS scope.Close(Boolean::New(true))
//
using namespace std;
using namespace v8;
using namespace node;


// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) {
	return *value ? *value : "<string conversion failed>";
}

//Send Msg Function
static Handle<Value> send_msg(const Arguments& args) {
	HandleScope scope;
	//Check for arguments
	if (args.Length() < 4 || args[0]->IsUndefined() || args[1]->IsUndefined() || args[2]->IsUndefined() || args[3]->IsUndefined()) {
		printf("Missing arguments on function send_msg in KiwiLib, exiting funciton NOW.");
		return RERROR;
	}
	
	//Get args
	int queueKeyID = args[0]->NumberValue();
	v8::String::Utf8Value strQueueID(args[1]);
	const char* messageQueueID = ToCString(strQueueID);
	v8::String::Utf8Value strWorkerPath(args[2]);
	const char* workerFilePath = ToCString(strWorkerPath);
	v8::String::Utf8Value strWorkerArgs(args[3]);
	const char* workerArgs = ToCString(strWorkerArgs);

	//sane as IPC_CREAT & 0777
	int queueCreationMask = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
	int msqid;	
	
	//Create
	if ((msqid = msgget(queueKeyID,queueCreationMask)) == -1) {
		perror("msgget failed:\n");
		return RERROR;
	} 
	//Okay, now let;s try to send it
	else {
		//Prepare
		struct mymsg {
			long int mtype;
			char     mtext[MaxMsgBuffer];
		};
		struct mymsg currentMessage;
		//Format new message
		char tmpString[MaxMsgBuffer];
		sprintf(tmpString,"%s||%s||%s",messageQueueID,workerFilePath,workerArgs);
		sprintf(tmpString,"s:%i:\"%s\";",(int)strlen(tmpString),tmpString);
		
		//Initialize new message
		strcpy(currentMessage.mtext,tmpString);
		currentMessage.mtype = 1;
		int msgsz = strlen(currentMessage.mtext);
		
		//Try to send it
		if (msgsnd(msqid, &currentMessage, msgsz, IPC_NOWAIT) == -1) {
			perror("msgsnd failed:\n");
			return RERROR;
		}
		return RSUCCESS;
	}
}

static void init(Handle<Object> target) {
	//Register Methods
	NODE_SET_METHOD(target, "send_msg", send_msg);
}
//Register module, and it initialization function
NODE_MODULE(Kiwi, init);
