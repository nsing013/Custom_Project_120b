
// Using ADC to get the x and y axis of the JOYSTICK
void ADC_init() 
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are in Free Running Mode, a new conversion will trigger whenever the previous conversion completes.
}

unsigned short Read_ADC(uint8_t ch)
{
	ADMUX = (1<<REFS0);
	ADCSRA |= (1 << ADEN) | (1 << ADPS2);
	ch = ch&0x07;
	ADMUX |= ch; //alternates between A0 and A1 which are the horizontal and vertical values on the joystick
	ADCSRA |= (1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA |= (1<<ADIF);
	return ADC;
}

enum Joystick_States {Joystick_Start, Joystick_pressed, Joystick_navigate} Joystick_State;

void Joystick_tick()
{
	switch(Joystick_State) //start transitions
	{
		case Joystick_Start:
			//if(joystick is pressed) go to state Joystick_pressed  //NO PRESS ON JOYSTICK use regular button
			//if(joystick is moved) go to state navigate.... well im not sure about this one
			break;
		
		case Joystick_pressed:
			//illuminate the led that cursor was on when the joystick was pressed //USE A BUTTON INSTEAD THERE IS NO BUTTON ON JOYSTICK DUMBB!
			break;

		case Joystick_navigate:
			//if(right, A0 value is greater than 5) increment x coordinate
			//if(left, A0 value is smaller than 5) decrement x coordinate
			//if(up,  A1 value is greater than 5) increment y coordinate
			//if(down, A1 value is greater than 5) decrement y coordinate
			break;
		
		default:
			Joystick_State = Joystick_Start;
			break;
	} //end of the transitions
	
	switch(Joystick_State) //state actions for what happens for the buttons below this
	{
		case Joystick_Start:
			break;
		case Joystick_pressed:
			break;
		case Joystick_navigate:
			break;
		default:
			break;
	}// end of the state actions
	
	//PORTC = output;
} //end of Button LA function