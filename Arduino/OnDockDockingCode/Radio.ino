//We must pass the char as well as either the data recieved from the sonar, or do calculations here and send the desired heading

void sendRadio()
{
  //delay(1000);  // Wait 1 second between transmits, could also 'sleep' here!
  char radiopacket[50];    //creates a character array to send information over the radio. This is the only allowable format

  for (int i = 0; i < 51; i++)
  {
    radiopacket[i] = 0;
  }

  char node[10];           //creates a temporary character array
  itoa(nodeNumber, node, 10); //places the value "nodeNumber" into a character array
  char xValue[10];
  itoa(xAxis, xValue, 10);
  char yValue[10];
  itoa(yAxis, yValue, 10);
  char button[10];
  itoa(buttonNumber, button, 10);
  const char *delimiter = ",";  // a delimiter is what defines the seperations in your string/array
  char bufferVal[10];
  int bufferValue = 0;
  itoa(bufferValue, bufferVal, 10);

  strcpy(radiopacket, node);    // copies the character array "node" into radiopacket
  strcat(radiopacket, delimiter); // concatenate (tacks on the end) the delimiter character
  strcat(radiopacket, button); // concatenate (tacks on the end) the character array "button"
  strcat(radiopacket, delimiter);
  strcat(radiopacket, yValue);
  strcat(radiopacket, delimiter);
  strcat(radiopacket, xValue);


  //itoa(packetnum++, radiopacket + 13, 10); // adds the number of packet being sent. I don't think we need this.
  Serial.print("Sending "); Serial.println(radiopacket); //serial prints what is being sent

  rf95.send((uint8_t *)radiopacket, strlen(radiopacket));  //sends the unsigned 8 bit integer from ram at the address "radiopacket" and the length of the radiopacket
  rf95.waitPacketSent(); //unsure what this does. I assume it creates a minimal delay for radio clarity.
}
