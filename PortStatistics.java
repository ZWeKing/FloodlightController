        String dpid="00:00:00:00:00:00:00:03";
    	long switchId=HexString.toLong(dpid);
    	IOFSwitch sw = floodlightProvider.getSwitches().get(switchId);
        Future<List<OFStatistics>> future;
        List<OFStatistics> values = null;
    	
    	OFStatisticsRequest req = new OFStatisticsRequest();
    	req.setStatisticType(OFStatisticsType.PORT);
        int requestLength = req.getLengthU();
        
        OFPortStatisticsRequest specificReq = new OFPortStatisticsRequest();
        specificReq.setPortNumber((short)OFPort.OFPP_NONE.getValue());
        req.setStatistics(Collections.singletonList((OFStatistics)specificReq));
        requestLength += specificReq.getLength();
        
        req.setLengthU(requestLength);
        
        try {
            future = sw.getStatistics(req);
            values = future.get(10, TimeUnit.SECONDS);
        } catch (Exception e) {
            logger.error("Failure retrieving statistics from switch " + sw, e);
        }
       //输出收集到的信息 
        Iterator<OFStatistics> iterator=values.iterator();
        while(iterator.hasNext()){
        	OFPortStatisticsReply portReply=(OFPortStatisticsReply)iterator.next();
        	if(portReply.getPortNumber()==4){
        	logger.info("switch Port receive bytes:{}  switch Port receive packets:{}",
            			portReply.getReceiveBytes(),portReply.getreceivePackets());	
        	}
        	
        }
