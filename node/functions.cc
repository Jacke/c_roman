#include "functions.h"
#include "../number_converter.h"


NAN_METHOD(nothing)
{
}

NAN_METHOD(aString)
{
  info.GetReturnValue().Set(Nan::New("This is a thing.").ToLocalChecked());
}

NAN_METHOD(aBoolean)
{
  info.GetReturnValue().Set(false);
}

NAN_METHOD(aNumber)
{
  info.GetReturnValue().Set(1.75);
}

NAN_METHOD(anObject)
{
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("key").ToLocalChecked(), Nan::New("value").ToLocalChecked());
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(anArray)
{
  v8::Local<v8::Array> arr = Nan::New<v8::Array>(3);
  Nan::Set(arr, 0, Nan::New(1));
  Nan::Set(arr, 1, Nan::New(2));
  Nan::Set(arr, 2, Nan::New(3));
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(fromRoman)
{

  v8::Isolate *isolate = info.GetIsolate();
  auto context = isolate->GetCurrentContext();
  //v8::String arg = info[0]->ToString(context).ToLocalChecked();

  // v8::String::Utf8Value utf8(info[0]->ToString(context));
  // int len = utf8.length() + 1;
  // char *str = (char *) calloc(sizeof(char), len);
  // strncpy(str, *utf8, len);

  // std::string str(*v8::String::Utf8Value(info[0].As<v8::String>());

  //v8::String::Utf8Value utfValue(str);

  //char* parsedValue = *value ? *value : "<string conversion failed>";
  
  v8::Local<v8::String> test = info[0].As<v8::String>();
  v8::String::Utf8Value resultt(isolate, test);
  const char* parsedValue = *resultt ? *resultt : "<string conversion failed>";

  // v8::String::NewFromUtf8 
  Nan::Utf8String utf8_value(info[0]);
  int len = utf8_value.length();
  if (len <= 0) {
     return Nan::ThrowTypeError("arg must be a non-empty string");
  }
  std::string string_copy(*utf8_value, len);

  int result = proccessNumber((char*) parsedValue);//string_copy.c_str());
  info.GetReturnValue().Set(result);
}

NAN_METHOD(toRoman)
{
  v8::Isolate *isolate = info.GetIsolate();
  std::string str ("Please split this sentence into tokens"); 
  std::string a = decimal_to_roman(Nan::To<int>(info[0]).FromJust());
  // std::string arg0 = *Nan::Utf8String(info[0]);

  v8::Local<v8::String> returned_str = v8::String::NewFromUtf8(isolate, a.c_str(), 
    v8::NewStringType::kNormal).ToLocalChecked();

  info.GetReturnValue().Set(returned_str);
}

NAN_METHOD(callback)
{
  v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
  Nan::AsyncResource *resource = new Nan::AsyncResource(Nan::New<v8::String>("MyObject:CallCallback").ToLocalChecked());
  resource->runInAsyncScope(Nan::GetCurrentContext()->Global(), callbackHandle, 0, 0);
}

NAN_METHOD(callbackWithParameter)
{
  v8::Local<v8::Function> callbackHandle = info[0].As<v8::Function>();
  Nan::AsyncResource *resource = new Nan::AsyncResource(Nan::New<v8::String>("MyObject:CallCallbackWithParam").ToLocalChecked());
  int argc = 1;
  v8::Local<v8::Value> argv[] = {
      Nan::New("parameter test").ToLocalChecked()};
  resource->runInAsyncScope(Nan::GetCurrentContext()->Global(), callbackHandle, argc, argv);
}

// Wrapper Impl

Nan::Persistent<v8::Function> MyObject::constructor;

NAN_MODULE_INIT(MyObject::Init)
{
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "plusOne", PlusOne);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("MyObject").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

MyObject::MyObject(double value) : value_(value)
{
}

MyObject::~MyObject()
{
}

NAN_METHOD(MyObject::New)
{
  if (info.IsConstructCall())
  {
    double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
    MyObject *obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  }
  else
  {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor);
    info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
  }
}

NAN_METHOD(MyObject::PlusOne)
{
  MyObject *obj = Nan::ObjectWrap::Unwrap<MyObject>(info.This());
  obj->value_ += 1;
  info.GetReturnValue().Set(obj->value_);
}
