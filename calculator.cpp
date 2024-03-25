#include "calculator.h"

// static 변수 초기화
Napi::FunctionReference* Calculator::functionRef =
    new Napi::FunctionReference();

// Javasciprt 클래스 생성 및 초기화
Napi::Function Calculator::Init(const Napi::Env env) {
  // 클래스 생성
  Napi::Function func =
      DefineClass(env, "Calculator",
                  {InstanceMethod("add", &Calculator::Add),
                   InstanceMethod("subtract", &Calculator::Subtract),
                   InstanceMethod("multiply", &Calculator::Multiply),
                   InstanceMethod("divide", &Calculator::Divide),
                   InstanceMethod("getValue", &Calculator::GetValue)});

  // 클래스 생성 후 functionRef에 저장 (Persistent 함수는 GC 대상 제외시킴)
  *Calculator::functionRef = Napi::Persistent(func);

  return func;
}

// 팩토리 함수
Napi::Object Calculator::From(Napi::Env env, Napi::Value arg) {
  Napi::Object obj = Calculator::functionRef->New({arg});
  return obj;
}

// 생성자
Calculator::Calculator(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Calculator>(info) {
  Napi::Env env = info.Env();

  // 인자가 없거나 숫자가 아닌 경우 에러 처리
  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return;
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = value.DoubleValue();
}

Napi::Value Calculator::GetValue(const Napi::CallbackInfo& info) {
  double num = this->value_;

  return Napi::Number::New(info.Env(), num);
}

Napi::Value Calculator::Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = this->value_ + value.DoubleValue();

  return Calculator::GetValue(info);
}

Napi::Value Calculator::Subtract(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = this->value_ - value.DoubleValue();

  return Calculator::GetValue(info);
}

Napi::Value Calculator::Multiply(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Number multiple;

  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = this->value_ * value.DoubleValue();

  return Calculator::GetValue(info);
}

Napi::Value Calculator::Divide(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int length = info.Length();
  if (length <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return env.Null();
  }

  const Napi::Number value = info[0].As<Napi::Number>();
  this->value_ = this->value_ / value.DoubleValue();

  return Calculator::GetValue(info);
}