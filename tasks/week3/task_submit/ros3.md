ros笔记3
1.	Service
bool callback(srv_type::Request& req, srv_type::Response& res) 
ros::ServiceServer server = nh.advertiseService(srv_name, callback)
ros::spin()
2.	Client
srv_type srv
srv.request = …
ros::ServiceClient client = nh.serviceClient<srv_type>(srv_name)
client.call(srv)
srv.response 保存了响应数据
3.	dynamic_reconfigure
	一个旨在将节点得参数的子集暴露出来以供外界在节点运行时配置的package。
	需要在包的cfg文件夹下配置一个.cfg后缀的python文件来生成相应的代码。可以使用命令行dynparam（要rosrun）来使用，也可维护一个dynamic_reconfigure::Server<config>动态参数服务器。注：需要绑定一个回调，但参数存取是自动完成的，回调只供方便调试等。取参数直接用nh.getParam(“/node/param”, var)获取。
	可以使用rqt_reconfigure工具从GUI改变参数。

