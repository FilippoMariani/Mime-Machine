/* PROGRAM NAME: Mime
AUTHOR: Filippo Mariani
04/01/22 (dd/mm/yy)
 <> */

unsigned int actionData[2][60];
int arrayPosition=0;
int actionBegin=0;
int actionEnd=0;
bool previousAction[3]={false, false, false};

int index=0;
int indexd=0;

int storage(int a, int b, int btnNumber)
{
  int duration=a-b;
  actionData[0][arrayPosition+1]=btnNumber;
  actionData[1][arrayPosition]=duration;
  arrayPosition=arrayPosition+1;
  actionBegin=millis();
}

int signial()
{
  delay(500);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  delay(100);
}

void setup() 
{
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(7, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  for(index=0; index<2; index++)
  {
    for(indexd=0; indexd<60; indexd++)
    {
      actionData[index][indexd]=0; 
    }
  }
}

void loop() 
{
  //reinizializzazione delle variabili
  arrayPosition=0;
  previousAction[0]=false;
  previousAction[1]=false;
  previousAction[2]=false;
  for(index=0; index<2; index++)
  {
    for(indexd=0; indexd<60; indexd++)
    {
      actionData[index][indexd]=0; 
    }
  }
  signial(); //segnale
  actionBegin=millis();
  while(true) //fase di memorizzazione
  {
    actionEnd=millis();
    if(digitalRead(2)==HIGH)
    {
      if(previousAction[0]==false)
      {
        storage(actionEnd, actionBegin, 1);
      }
      previousAction[0]=true;
    }
    else if(digitalRead(2)==LOW)
    {
      if(previousAction[0]==true)
      {
        storage(actionEnd, actionBegin, 1);
      }
      previousAction[0]=false;
    }
    if(digitalRead(4)==HIGH)
    {
      if(previousAction[1]==false)
      {
        storage(actionEnd, actionBegin, 2);
      }
      previousAction[1]=true;
    }
    else if(digitalRead(4)==LOW)
    {
      if(previousAction[1]==true)
      {
        storage(actionEnd, actionBegin, 2);
      }
      previousAction[1]=false;
    }
    if(digitalRead(7)==HIGH)
    {
      if(previousAction[2]==false)
      {
        storage(actionEnd, actionBegin, 3);
      }
      previousAction[2]=true;
    }
    else if(digitalRead(7)==LOW)
    {
      if(previousAction[2]==true)
      {
        storage(actionEnd, actionBegin, 3);
      }
      previousAction[2]=false;
    }
    if(actionEnd-actionBegin>=4000 || arrayPosition>=58)
    {
      break;
    }
  }
  
  signial();
  for(index=0; index<60; index++) //fase di ripetizione
  {
    switch(actionData[0][index])
    {
      case(1):
        if(digitalRead(13)==LOW)
        {
          digitalWrite(13, HIGH);
        }
        else
        {
          digitalWrite(13, LOW);
        }
        break;
      case(2):
        if(digitalRead(12)==LOW)
        {
          digitalWrite(12, HIGH);
        }
        else
        {
          digitalWrite(12, LOW);
        }
        break;
      case(3):
        if(digitalRead(8)==LOW)
        {
          digitalWrite(8, HIGH);
        }
        else
        {
          digitalWrite(8, LOW);
        }
    }
    delay(actionData[1][index]);
  }
  signial();
  while(digitalRead(2)!=HIGH) //l'autorizzazione a ripetere viene data con la pressione del primo pulsante
  {
  }
}
