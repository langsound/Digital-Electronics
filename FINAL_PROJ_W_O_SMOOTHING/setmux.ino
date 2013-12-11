void setMuxChannel(int channelNumber){
  digitalWrite(muxS0, channelNumber & 1);  // dec to binary conversion for 1s place
  digitalWrite(muxS1, channelNumber & 2);
  digitalWrite(muxS2, channelNumber & 4);
  digitalWrite(muxS3, channelNumber & 8);

}//end setMuxChannel

