public void portDown(IOFSwitch sw, OFMessage msg, FloodlightContext cntx){
		
		//实例化OFPacketIn命令
		OFPacketIn pi=(OFPacketIn)msg;
		//被操作的交换机的实例化
		OFSwitchImpl ofs=(OFSwitchImpl)sw;
		short portNumber=pi.getInPort();
		System.out.println(msg.getType());
		System.out.println(portNumber);
		//openflow交换机的物理地址
		byte[] macAddress=ofs.getPort(portNumber).getHardwareAddress();
		//定义OFPortMod命令
		OFPortMod mymod=(OFPortMod)floodlightProvider.getOFMessageFactory().getMessage(OFType.PORT_MOD);
		//设置OFPortMod命令的相关参数
		mymod.setPortNumber(portNumber); 
		mymod.setConfig(OFPhysicalPort.OFPortConfig.OFPPC_PORT_DOWN.getValue());
		mymod.setHardwareAddress(macAddress);
		mymod.setMask(0xffffffff);
		//将OFPortMod命令发送到指定的交换机中，进行执行！
		try{
			sw.write(mymod,cntx);
			logger.info("PortDown success!");
		}catch(Exception e){
			logger.info("PortDown Failed");
		}	
		return;
		
	}
