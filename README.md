# basetrojan
一个简单的后台监听木马的原型机。

客户端采用c++的win32编程，服务器使用python脚本来接收客户端发送的内容，中间的连接是udp协议。

//作者逐渐更新中，武汉加油

* 0开头的版本，均没有任何威胁性，只会将一个字符串“example”发送到作者的服务器上。

## v0.1
运行后隐藏窗口，在后台实现每五分钟发送“example”到服务器，如果服务器的python脚本在运行中，则收到信息并记录时间，ip，信息内容。
> 将项目->属性->c/c++->sdl（全程序优化）改为否 即可编译（基于VS2017）

## v0.2
在win10下与v0.1没有什么区别，但是在xp虚拟机下发现无法运行，在xp及IDE vs2010上可以作如下设置进行编译通过
> 改一下Project---->xiazai Properties--->Linker--->Advanced--->Entery Point修改为"mainCRTStartup"。
Project---->xiazai Properties--->Linker--->System-->Subsystem改成Windows（/SUBSYSTEM:WINDOWS）

在xp虚拟机下，360安全卫士可以将其报毒：Generic/Trojan.B0.c8b，但是加上一个upx壳即可避免之。
有人推荐我用360杀毒来搞，可以查出：HEUR/QVM11.1.2B19.Malware.Gen(加壳)，而不带壳的程序则不报毒

## v0.3
不太稳定的版本，能够实现用两次运行（囧）将自身拷贝到系统启动菜单，实现开机自启动。如果是开机自启动的程序，则能够如之前版本一样发送example。

360杀毒在不加壳的情况下同样不会报毒。
