I have long been working in environments where engineers insist to use
different *best* languages to program their micro-services.  This
intrigued my interest to write Go servers that can be called by
programs in various languages.

I saw dozens of implementations of JSON RPC, XML RPC, and protobuf RPC
(including Google gRPC), plus RPC implementations using other wire
formats, like Thrift and MsgPack.  I am surprised that none of them
helps me write less code (in various languages generally) than the Go
built-in JSON RPC `net/rpc/jsonrpc` package does.

So I wrote this example, which includes a Go JSON RPC server, stolen
from https://www.artima.com/weblogs/viewpost.jsp?thread=333589, and a
C++ client.  This example shows how simple we can write a client
talking to Go JSON RPC servers based on the `net/rpc/jsonrpc` package:
we simply make a TCP socket connection to the server, and fire RPC
calls as a JSON payload:

```
{  
   "id":1, 
   "method":"RPCFunc.Echo", 
   "params":[ 
      "apple" 
   ] 
}
```

where `"method"` specifies the RPC method, and `"params"` is JSON
encoding of the argument of that method. `"id"` is the identification
of the invocation.

Then we read the same connection, and get responses like:
```
{
   "id":1,
   "result":"apple",
   "error":null
}
```

where `"result"` is the JSON-encoded return value, and `"id"`
identifies the invocation.

<!--  LocalWords:  JSON protobuf gRPC MsgPack Go's RPCFunc params
 -->
