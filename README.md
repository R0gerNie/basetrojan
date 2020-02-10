# basetrojan
一个简单的后台监听木马的原型机。

客户端采用c++的win32编程，服务器使用python脚本来接收客户端发送的内容，中间的连接是udp协议。

* 0开头的版本，均没有任何威胁性，只会将一个字符串“example”发送到作者的服务器上。

## v0.1
运行后隐藏窗口，在后台实现每五分钟发送“example”到服务器，如果服务器的python脚本在运行中，则收到信息并记录时间，ip，信息内容。
> 将项目->属性->c/c++->sdl（全程序优化）改为否 即可编译（基于VS2017）

## v0.2
在win10下与v0.1没有什么区别，但是在xp虚拟机下发现无法运行，在xp及IDE vs2010上可以作如下设置进行编译通过
> 改一下Project---->xiazai Properties--->Linker--->Advanced--->Entery Point修改为"mainCRTStartup"。
Project---->xiazai Properties--->Linker--->System-->Subsystem改成Windows（/SUBSYSTEM:WINDOWS）



