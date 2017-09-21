#include <node.h>
#include <v8.h>

using namespace v8;

// 传入了两个参数，args[0] 字符串，args[1] 回调函数
void hello(const FunctionCallbackInfo<Value>& args) {
  // 使用 HandleScope 来管理生命周期
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  // 判断参数格式和格式
  if (args.Length() < 2 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // callback, 使用Cast方法来转换
  Local<Function> callback = Local<Function>::Cast(args[1]);
  Local<Value> argv[1] = {
    // 拼接String
    String::Concat(Local<String>::Cast(args[0]), String::NewFromUtf8(isolate, " world"))
  };
  // 调用回调, 参数: 当前上下文，参数个数，参数列表
  callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);
}

// 相当于在 exports 对象中添加 { hello: hello }
void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", hello);
}

// 将 export 对象暴露出去
// 原型 `NODE_MODULE(module_name, Initialize)`
NODE_MODULE(test, init);

// 作者：xun
// 链接：http://www.jianshu.com/p/857b4d38aba1
// 來源：简书
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。