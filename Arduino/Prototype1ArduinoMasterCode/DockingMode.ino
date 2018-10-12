void dock()
{
  dockingStatus++;

  if (dockingStatus == 0)
  {
    delay(30000);
    //full forward motors
    dockingMode == false;
  }

  else if (dockingStatus == 1)
  {
    // do something fancy and dock
    dockingStatus++;
  }

  else if (dockingStatus == 2)
  {
    delay(30000);
    //full reverse motors
    dockingStatus = 0;
    dockingMode == false;
  }

}

