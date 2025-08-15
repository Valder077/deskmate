## Total 42 hours 
# 5-6 July(Sorry the timings of the documentation isn't very exact bc i forgot lol) (1 hour)
So basically my idea for this project stems from the fact that I would generally say that I have a pretty packed schedule every single day. School until 4 and Dragon Boat training from 5-7.30 and I come back home at 8.30 every single day to do my homework. 

So most of my studying and homework gets done quite late in the night when its all quiet in the house and I can't lie sometimes it tends to gets hard to stay motivated to study. 

So I figured that, what if I just make a little desk pet type of thing that would keep me company during all those late-night study sessions everyday? I mean, I've already seen similar ideas come out like for instance like the Dasai Mochi which is a driving companion that has facial expressions and sounds that change based on the car's movement. And ofcourse theres the all popular tamagotchi which is a sort of a digital pet. So, when all these exist, why not one for studying? 

Okay, but i guess the small problem is I don't know anything about hardware so i guess its time for some research. 

After a few hours of research I kind of crafted a solid idea of what i wanted to do and roughly the parts i would require. 

I basically wanted to make a relatively small deskmate that gives kind of a cute and homely vibe so that it encourages you to push on with your work. At its core, its going to have an oled screen in the middle, with 4 tactile switches below it that make it do certain things. As of now I want 

- 1 switch that gives it food and makes the "pet" eat the food and have heart shaped eyes
-1 switch that does something else thats funny(sorry its late at night my creative juices are running out)
-1 switch starts/stops a pomodoro timer 
-1 switch resets the timer 

I also plan to add a keychain hole at the side because I'm a guy who needs a constant change in environment when studying so I like to vary the places i study at.(library, school, home etc.). So making my deskmate highly portable is one of my key goal.

I wanted to add a pen holder case but i dont want to make him too clunky and not so portable. 


# 8 July 1.5 hours

Okay sorry dipped for a while because I was rushing some school stuff and also had hackpad submissions before undercity. Today was the day i do my schematic yay. 

![schematic](https://github.com/Valder077/deskmate/blob/main/img/schematic.jpg?raw=true)
![pcbdesk](https://github.com/Valder077/deskmate/blob/main/img/pcbdesk.jpg?raw=true)

Ngl, i really wanted to add leds at the sides of the screen so my deskmate can blush when i feed him/ show him some love but I'm not too familiar with using LEDs and I would need resistors too and I dont know if I would have time to source all these after undercity when i submit this project given I have some tests after undercity too. 


ALSO MAJOR PROBLEM I wanted to add tactile switches but I am not sure if i wired them properly and I asked slack for help but people there aren't too sure too so I decided to not take the risk and switch them out with keyboard switches (haha) since I love fidgeting with keyboard switches and find the clicking so satisfying and I figured I could make the keycaps look really cute(hopefully i cook this in the future).

This is how my PCB is going to look. 

Not going to lie figuring out the wiring for the tactile switches and then wiring all the led's and then deciding against it took some time but hey its all a learning process and I loved every second of it. 


# 9 July (3 hours)
Today I worked on CAD (my favourite part). Honestly back when i was doing the hackpad I crashed out so hard because I was new to fusion and my laptop is like from the 1900s so it was practically overheating the second i started up fusion, but honestly once you understand it its quite fun. 

Turns out I dont have pictures from the progress I made that day because im doing this journal entry a whole week later but you can take a look at the finished CAD. 

![bottom](https://github.com/Valder077/deskmate/blob/main/img/bottom.jpg?raw=true)

On this day I had finished the bottom casing to an extent(basic without any extra things)


# 17 July (2 hours)

Hi its been very many days and thats because i went to undercity. The event was so fire and I talked to so many new people and honestly one of the most surreal experiences of my life. But okay back to locking in. Today CAD is finished with all my extra decoration i added. I made his arms into lego like arms too since i thought they were cute and added some ears too. Added a base because I realised he may be a bit too thin for stability and added the keychain hole too. Finished up the top case of the deskmate too and really took quite a long time for adjusing the placement of the holes. But yay our CAD's done now!! Honestly I'm proud of how he looks though i wanted a bigger oled screen but i already have a 0.96 inch and I dont want to waste time ordering a bigger one. Now, all thats left is for me to sort out the functionality of the oled screen and draw out our deskmate. 

![top](https://github.com/Valder077/deskmate/blob/main/img/top.jpg?raw=true)
![full](https://github.com/Valder077/deskmate/blob/main/img/full.jpg?raw=true)
![deskcomponent](https://github.com/Valder077/deskmate/blob/main/img/deskcomponent.png?raw=true)


# 21 July (3.5 hours)

Hi I've been quite busy after undercity because I took a leave from school and there's so much things to catch up on. But today, we work on our oled screen animations. So heres a few clips of how our deskmate is going to look like. Finished up the normal face, eating face (1st switch), and  a bit of the    animations for the 2nd switch. However, I feel like i can only ensure all the animations work properly once I get my actual hardware components so I will probably refine the firmware then because I will be able to experiment with it. I had to research a lot for this part because this stuff was really new to me but we did it!!!!

![smile](https://github.com/Valder077/deskmate/blob/main/img/smile.jpg?raw=true)

This is another face due to the first switch:

![heart](https://github.com/Valder077/deskmate/blob/main/img/heart.png?raw=true)



# 23 July (2 hours)
Today I did some research again and finally finished the firmware for the pomodoro timer which the 3rd and 4th switch will control AND WE'RE DONE!!! Heres a picture of how its going to look like. 

![timer](https://github.com/Valder077/deskmate/blob/main/img/timer.png?raw=true)

# 25 July (1.5 hours)
Had to make some final refinements to the CAD to make it a bit more polished and had to update a lot of files in my repo and update my journal because i forgot again lol. 

# 2 August (3 hours)
Finally bought all my parts and tried soldering them. However, I had some soldering issues with the esp32s3 so i guess i'll continue with that another day 
(forgot to take pic of post soldering lol)

Painted my entire deskmate and had to repaint a few layers too since it didn't stick very well.
![basepic](https://github.com/Valder077/deskmate/blob/main/img/basepic.jpg?raw=true)
![basepic2](https://github.com/Valder077/deskmate/blob/main/img/basepic2.jpg?raw=true)
![evthpic](https://github.com/Valder077/deskmate/blob/main/img/evthpic.jpg?raw=true)



# 3 August (2 hours)
Tried to solder my ESP32 and the solder kept joining but I finally soldered it correctly and tried to make it work but I could not get the oled screen to work :C. I figured out that I had soldered it wrong which means I need to probably buy a new ESP32s3

# 4 August (1 hour)
I spent some time trying to purchase a new ESP32 but every place I went to (including the place I initially bought it from) was sold out. So I spent some time reasearching for alternatives.

# 5 August (5 hours)
MY HACKPAD KIT CAME. This means I have an extra RP2040 I can use since I had bought my own for my hackpad. I bought some jumper wires too and decided to manually wire and solder everything (i just wired the oled screen today not the key switches) and MY OLED WORKS!!!
![smilepic](https://github.com/Valder077/deskmate/blob/main/img/smilepic.jpg?raw=true)
![wirepic](https://github.com/Valder077/deskmate/blob/main/img/wirepic.jpg?raw=true)




# 6 August (4 hours)
I realised my firmware had quite a few issues so i decided to fix the firmware for each animation and also draw new animations over the next few days. Today I spent some time fixing my clock timer!
![timerpic](https://github.com/Valder077/deskmate/blob/main/img/timerpic.jpg?raw=true)



 # 7 August (5 hours)
 Wired all my keyswitches too.
 Had a lot of issues with rive when making animations so I had to redo a few of the animations. Made it such that my first two buttons work too (All the buttons work now!!)
 ![animpic](https://github.com/Valder077/deskmate/blob/main/img/animpic.jpg?raw=true)


# 8 August (3 hours)
Had to do some trouble shooting since I had issues like my oled screen animations came upside down, or in the wrong colour (white background black lines instead)
Heres an example of something that went wrong:

![wrongpic](https://github.com/Valder077/deskmate/blob/main/img/wrongpic.jpg?raw=true)


# 10 August (3 hours)
Made my poster!
![posterpic](https://github.com/Valder077/deskmate/blob/main/img/poster.jpg?raw=true)


