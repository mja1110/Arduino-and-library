
bool TCPSendData( byte Retry)
{
  for ( byte i = 0; i <= Retry; i++)
  {
    if (PostTCP( 2))
    {
      SimDeepSleep();
      return true;
    }
    delay(2000);
      ResetNetwork();
  }
  SimDeepSleep();
  return false;
}

bool TCPSendData()
{
  if (PostTCP( 0)) return true;
  return false;
}

bool _TCPSetup()
{
  SIM_buffer_flush();
  if (!SIM_sendCommand("AT+ cipshut", "ok", 2000)) return false;
  if (!SIM_sendCommand("AT + CIPMUX=0", "ok", 2000))return false;
  if (!SIM_sendCommand("AT+ CGATT=1", "ok", 2000))return false;
  if (!SIM_sendCommand("AT+CSTT = \"bsnlnet\",\"\",\"\" ", "ok", 2000))return false;
  if (!SIM_sendCommand("AT+CIICR", "ok", 2000))return false;
  if (!SIM_sendCommand("AT+CIFSR", "10.", "9.", 4000))return false;
  SIM_sendCommand("AT+CIPSPRT=1", "ok", 2000);
  return true;
}


bool PostTCP( byte Retry)
{
  if (!SIM_begin(10)) return false;
  if (!_TCPSetup()) return false;

#ifdef DEBUGER
  Serial.println(F("-------------------- -Start posting-----------------------"));
#endif
  for ( byte i = 0; i <= Retry; i++)
  {
    if (SIM_sendCommand("AT+ CIPSTART =\"TCP\",\"184.106.153.149\",\"80\" ", "connect ok", "already", 5000))
    {
      SIM_sendCommand("AT + CIPSTATUS", 2000);
      String DataStrThink = msgGPRS + DataStr.DataStringSend;
      if (SIM_sendCommand("AT + CIPSEND = " + (String)(DataStrThink.length() + 2), ">", 2000))
      {
        SIM_sendCommand(DataStrThink, "closed", "send ok", 10000);
        SIM_sendCommand("AT + CIPCLOSE", 2000);
        SIM_sendCommand("AT + CIPSHUT", 4000);
#ifdef DEBUGER
        Serial.println(F("-------------------- -Posting finished---------------------- -"));
#endif
        return true;
      }
      SIM_sendCommand("AT + CIPCLOSE", 2000);
      SIM_sendCommand("AT + CIPSHUT", 4000);
    }
  }
  return false;
}
