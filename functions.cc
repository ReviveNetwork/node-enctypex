#include "functions.h"
#include <iostream>
#include "v8.h"
#include <string.h>

extern "C" int enctypex_quick_encrypt(unsigned char *key, unsigned char *validate, unsigned char *data, size_t size);

using namespace std;
using namespace v8;
using namespace node;

NAN_METHOD(encode) {

    // Validate things
    if (info.Length() < 4) return;

    if (!info[3]->IsFunction()) return;
    Nan::Callback callback(Local<Function>::Cast(info[3]));

    if (info[0].IsEmpty() || !info[0]->IsObject()){
        Local<Value> argv[1] = { Nan::New<String>("Argument 1 (inputData) is empty or not a Buffer").ToLocalChecked() };
        callback.Call(1, argv);
        return;
    }

    if (info[1].IsEmpty() || !info[1]->IsObject()){
        Local<Value> argv[1] = { Nan::New<String>("Argument 2 (key) is empty or not a Buffer").ToLocalChecked() };
        callback.Call(1, argv);
        return;
    }

    if (info[2].IsEmpty() || !info[2]->IsObject()){
        Local<Value> argv[1] = { Nan::New<String>("Argument 3 (validate) is empty or not a Buffer").ToLocalChecked() };
        callback.Call(1, argv);
        return;
    }

    // get the key from buffer argument
    Local<Object> keyBuffer = info[1]->ToObject();
    int len = Buffer::Length(keyBuffer);
    unsigned char* key = new unsigned char[len + 1];
    memcpy((void*)key, (void*)Buffer::Data(keyBuffer), len);
    key[len] = 0;

    // get the validate from buffer argument
    Local<Object> validateBuffer = info[2]->ToObject();
    len = Buffer::Length(validateBuffer);
    unsigned char* validate = new unsigned char[len + 1];
    memcpy((void*)validate, (void*)Buffer::Data(validateBuffer), len);
    validate[len] = 0;

    // get our data from the buffer
    Local<Object> dataBuffer = info[0]->ToObject();
    int dataLen = Buffer::Length(dataBuffer);
    unsigned char* data = new unsigned char[dataLen + 1];
    memcpy((void*)data, (void*)Buffer::Data(dataBuffer), dataLen);
    data[dataLen] = 0;

    // realloc to account for header the following method will inject
    data = (unsigned char*)realloc(data, dataLen + 23);

    int newSize = enctypex_quick_encrypt(key, validate, data, dataLen);

    delete key;
    delete validate;

    // Call our callback
    Local<Value> argv[2] = { Nan::Null(), Nan::NewBuffer((char*)data, newSize).ToLocalChecked() };
    callback.Call(2, argv);
}
