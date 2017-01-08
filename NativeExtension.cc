#include "functions.h"

using v8::FunctionTemplate;

// NativeExtension.cc represents the top level of the module.
// C++ constructs that are exposed to javascript are exported here

NAN_MODULE_INIT(InitAll) {
    Nan::Set(target, Nan::New("encode").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(encode)).ToLocalChecked());
    Nan::Set(target, Nan::New("decode").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(decode)).ToLocalChecked());
    
    Nan::Set(target, Nan::New("encode2").ToLocalChecked(), Nan::GetFunction(Nan::New<FunctionTemplate>(encode2)).ToLocalChecked());
}

NODE_MODULE(NativeExtension, InitAll)
