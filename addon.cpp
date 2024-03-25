#include <napi.h>

#include "calculator.h"

Napi::Value CreateCalculator(const Napi::CallbackInfo& info) {
  return Calculator::From(info.Env(), info[0]);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  exports.Set("Calculator", Calculator::Init(env));
  exports.Set("createCalculator", Napi::Function::New(env, CreateCalculator));
  return exports;
}

NODE_API_MODULE(addon, InitAll);