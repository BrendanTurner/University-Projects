"use strict"; // for future-proof error-fixing

// define global variable here
var canvas = document.getElementById('canvas');
var context = canvas.getContext('2d');
var width = canvas.width;									// shortcut for later so canvas.width doesnt need to be referenced each time
var height = canvas.height;									//same but with height
var player_1_score = 0;										//int variable to store player 1's score
var player_2_score = 0;										//same again but for player 2

//create objects here
var ball = new Ball();										//creat the ball instance
var player_2 = new Paddle(10, 0);							//create the left paddle
player_2.y_position = (height * 0.5) - (player_2.height/2);	//set the y position of the paddle
var player_1 = new Paddle(width-15,0);						//create the left paddle
player_1.y_position = (height * 0.5) - (player_1.height/2);	//set the y position of the paddle
var top_boundary = new Boundary(10,15);						//set boundary at top of screen
var bottom_boundary = new Boundary(10,height-20);			//set boundary at bottom of screen

// paddle constructor function
function Paddle(x_position, y_position){
	this.width = 5; 										// width in pixels
	this.height = 50; 										// height in pixels
	this.x_position = x_position; 							// position in pixels
	this.y_position = y_position; 							// position in pixels
}

// method to draw paddles
Paddle.prototype.render = function(){
	context.fillRect(this.x_position, this.y_position, this.width, this.height); // draw paddle
};

//method to move paddle up
Paddle.prototype.move_up = function(){
	if(this.y_position > 20){								//if the paddle is lower(ie a greater number then the top boundary)
		this.y_position = this.y_position -10;				//then move the paddle up(decrease its y position by 10)
	}
}

//method to move paddle down
Paddle.prototype.move_down = function(){
	if (this.y_position < height-this.height-20){			//if the paddle is higher(ie a lower number then the bottom boundary)
		this.y_position = this.y_position +10;				//then move the paddle down(increase its y position by 10)
	}
}

// ball constructor function
function Ball(){
	var leftOrRight = true;									//boolean for whether the ball is traveling left or right
	this.speed =150;										//the global speed of the ball
	this.x_speed = 1; 										//this is different to the global speed fo use later in the ball update function
	this.y_speed = 0; 										//this changes when the ball hits a paddle off center
	this.ball_radius = 5; 									// size of the ball in pixels
	this.x_position = width * 0.5; 							//x position in pixels
	this.y_position = height * 0.5; 						//y position in pixels
	this.reset_x = this.x_position;							//stores the x position to be used later by the ball reset function
	this.reset_y = this.y_position;							//stores the y position to be used later by the ball reset function
}

// method to draw ball
Ball.prototype.render = function(){
	context.beginPath();									//start drawing the ball
	context.arc(this.x_position,							//draw an arc around the specified center of the ball
	this.y_position, this.ball_radius, 0, Math.PI * 2);
	context.fill();											//fill the ball in
}

//method to update ball
Ball.prototype.update = function(target_1,target_2,t_elapsed){
	for(var i = 0; i < this.speed; i++){															//this for variable uses the global speed of the ball,
																									//so it can check whether it has hit the paddle or not
																									//and not overshoot.
																									
		var angle_1 = Math.atan2((target_1.y_position + (target_1.height/2)) - this.y_position,		//create a vector that stores a point behind the paddle
		(target_1.x_position + (target_1.width*4)) - this.x_position);								//so the ball can calculate an angle to bounce of the paddle
																									//if it hits the edge of the paddle.
																									
		var angle_2 = Math.atan2((target_2.y_position + (target_2.height/2)) - this.y_position,		//same here but of the other side
		(target_2.x_position - (target_2.width*3.5)) - this.x_position);
		
		//reset ball if it goes of screen past paddles
		if(this.x_position > width||this.x_position<0){		//if the x position of the ball is ever outside of the canvas
			ball.reset_ball();								//then call the reset function
		}
		//update x and y positions based on the speed
		this.x_position += this.x_speed*t_elapsed;			//position becomes the speed value multiplyed by time that has passed
		this.y_position += this.y_speed*t_elapsed;			//and again
		
		//bounce off the paddles
		if((this.x_position <= (target_1.x_position + (target_1.width)))&&							//if the x position of the ball is inbetween
		(this.x_position >= (target_1.x_position))&&												//either side of the target paddle and
		(this.y_position <= (target_1.y_position + (target_1.height)))&&							//the y is inbetween
		(this.y_position >= (target_1.y_position))){												//the top and bottom of the target paddle.
		
			this.x_speed = this.x_speed*-1;															//reverse the x speed
			
			if((this.y_speed == 0)&&(this.y_position!=((target_1.y_position)+(target_1.height/2)))){//one of check to start the ball off on a bounce
				this.y_speed = Math.sin(angle_1);													//calculate an angle based on the vector from earlier.
				this.y_speed = this.y_speed*-1;														//reverse the y speed because 
			}																						//the angle is oposite to the way its meant to go initialy
			this.leftOrRight = true;																//set the boolean to state the ball is traveling the other way
		}
		
		if((this.x_position <= (target_2.x_position + (target_2.width)))&&							//rinse and repeat for the other side
		(this.x_position >= (target_2.x_position))&&												//
		(this.y_position <= (target_2.y_position + (target_2.height)))&&							//
		(this.y_position >= (target_2.y_position))){												//
			this.x_speed = this.x_speed*-1;															//
			if((this.y_speed == 0)&&(this.y_position!=((target_2.y_position)+(target_2.height/2)))){//
				this.y_speed = Math.sin(angle_2);													//
				this.y_speed = this.y_speed*-1;														//
			}																						//
			this.leftOrRight = false;																//
		}																							//
		
		//bounce of boundaries
		if(this.y_position >= height-25||this.y_position<=25){//if the ball y position meets the top or bottom boundaries(manualy set rather than interacting with the boundaries)
			this.y_speed = this.y_speed*-1;					  //reverse the y speed
		}
	}
}

//method to reset ball
Ball.prototype.reset_ball = function(){
	this.x_position = this.reset_x;								//set the x position back to the center
	this.y_position = this.reset_y;								//same for the y_position
	
	if(this.leftOrRight == true){								//if the ball was traveling left
		this.x_speed = -1;										//set the x speed to -1(continue travleling left)
		player_1_score++;										//increment player 1's score by 1
	}
	else{														//else if the ball was traveling right
		this.x_speed = 1;										//set the x speed to 1(continue travleling right)
		player_2_score++;										//increment player 2's score by 1
	}
	this.y_speed = 0;											//reset y speed to 0
}

//boundary constructor function
function Boundary(x_position, y_position){
	this.width = width-20; 										// width in pixels(size of canvas with 10 pixels of from either side)
	this.height = 5; 											// height in pixels
	this.x_position = x_position; 								// position in pixels(passed from arguments)
	this.y_position = y_position; 								// position in pixels
}

//method to draw boundaries
Boundary.prototype.render = function(){
	context.fillRect(this.x_position, this.y_position, this.width, this.height); // draw boundary((origin is in the top left of the boundary
};

//Done--TODO: Add data for top and bottom rectangles (i.e boundaries)--Done

function render(){
	context.fillStyle = 'tomato'; 								// set colour of components within the canvas
	context.clearRect(0, 0, width, height); 					// clear the canvas 
	ball.render();												// draw the ball
	player_1.render();											// draw player_1 paddle
	player_2.render();											// draw player_2 paddle
	top_boundary.render();										// draw top boundary
	bottom_boundary.render();									// draw bottom boundary
	context.fillStyle = 'white';								// set fillstyle to white for the score
	context.fillText("Player 1:" + player_1_score,10,10);		// write the score for player one positioned in the top left
	context.fillText("Player 2:" + player_2_score,width-57,10); // same for player 2 top right
	//Done--TODO: draw the paddle (player_2 / cpu)--Done
	//Done--TODO: Make sure to render the top and bottom rectangle (i.e boundaries)--Done
}

function update(t_elapsed){
	ball.update(player_1,player_2,t_elapsed);					//call the ball update function setting the 2 paddles
																//as targets for its arguments along with the time elapsed
	// Done--TODO: Update ball position based on time elapsed--Done
	// Done--TODO: Bounce the ball of top and bottom rectangles--Done
  	// Done--TODO: Record score and reset if ball goes passed the left or right paddle--Done
  	// Done--TODO: Bounce the ball off the paddle--Done
}

// have keyboard inputs (controls for the paddle)
function keyboard_input(event){									// create an event to check for keys pressed
	var key = event.keyCode;									// a variable to store the key code fo whatever key has been pressed
	console.log(event.keyCode); 								// use this to view key codes while debugin in the browser
	var nothing_handled = false;								// used at the end if a unused key is pressed
	
	switch(key){												//switch statement usign the variable that stored the key code
		case 38://up arrow
			player_1.move_up();									// if up has been pressed move player 1 up(right hand paddle)
			break;
		case 40://down arrow
			player_1.move_down();								//if down pressed move player 1 down
			break;
		case 87://W key
			player_2.move_up();									//if w then player 2 up ( left paddle)
			break;
		case 83://S key
			player_2.move_down();								//if s then player 2 down
			break;
		default:
			nothing_handled = true;								//anything else do nothing and set the boolean to true but dont break out of the switch
	}
	if(!nothing_handled) event.preventDefault();				//this stops unused key wrongly pressed from interfering with other parts of the web page
	// Done--TODO: Modify code so the paddle goes up and down but not outside the area of play. --Done
}

window.addEventListener("keydown", keyboard_input); 			// listen to keyboard button press

// main game loop
var previous; 
function main(timestamp){
	if (!previous) previous = timestamp; 						//start with no elapsed time
  	var t_elapsed = (timestamp - previous) / 1000;  			//work out the elapsed time
  	update(t_elapsed); 											//update the game based on elapsed time
  	render();													//call the draw function
  	previous = timestamp;  										//set the previous timestamp ready for next time
  	window.requestAnimationFrame(main); 						//ask browser to call this function again, when it's ready
	//Done--TODO: render scene here (e.g draw ball, draw paddle, top and bottom rectangle detection), this function already exist;--Done
}

window.requestAnimationFrame(main);								//initial call of the main loop(the whole thing starts here

