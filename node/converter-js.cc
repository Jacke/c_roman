// hello.cc
#include <string.h>
#include <node.h>
#include <cstdlib>

extern "C" {
	#include "gen_ext.h"
}

namespace genderjs {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;
using v8::Integer;
using v8::Handle;

// convert a v8::String to a (char*) -- any call to this should later be free'd
static inline char *TO_CHAR(Handle<Value> val) {
    String::Utf8Value utf8(val->ToString());

    int len = utf8.length() + 1;
    char *str = (char *) calloc(sizeof(char), len);
    strncpy(str, *utf8, len);

    return str;
}

void getGender(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  // Make sure we were passed a name argument
    if (args.Length() == 0) {
      isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid number of arguments.")));
      return;
    }

//  char name[] { "Jennifer" };
//  auto name = get(args[0], "");
//  char name[] { "Jen" };
  //auto name = args[0]->ToString();
  auto name = TO_CHAR(args[0]->ToString());
  int country = GENDER_DEFAULT_COUNTRY;

  // Get the string variable from the arguments
  

  // Get the gender of the name
  int result = get_gender_utf8(name, GENDER_COMPARE_EXPANDED_UMLAUTS, country);
//  char* s_result { ' ' };
//  sprintf(s_result, "%d", result);

  //args.GetReturnValue().Set(String::NewFromUtf8(isolate, "M"));
//  args.GetReturnValue().Set(String::NewFromUtf8(isolate, s_result));
//  args.GetReturnValue().Set(Number::New(isolate, result));
  args.GetReturnValue().Set(Number::New(isolate, result));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "getGender", getGender);
}

NODE_MODULE(addon, init)

}  // namespace demo

