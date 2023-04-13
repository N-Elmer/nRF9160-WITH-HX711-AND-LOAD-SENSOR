# nRF9160 WITH HX711 AND LOAD SENSOR
Managing power to sustain device 🔋🔌 working for extended periods

.. _hello_world:

Hello World
###########

Overview
********

A simple sample that can be used with any :ref:`supported board <boards>` and
prints "Hello World" to the console.

Building and Running
********************

This application can be built and executed on QEMU as follows:

.. zephyr-app-commands::
   :zephyr-app: samples/hello_world
   :host-os: unix
   :board: qemu_x86
   :goals: run
   :compact:

To build for another board, change "qemu_x86" above to that board's name.

Sample Output
=============

.. code-block:: console

    Hello World! x86

Exit QEMU by pressing :kbd:`CTRL+A` :kbd:`x`.

Hi  Vidar Berg (vibe) ,

Thanks for your support. With the insights you gave, and that of my colleagues, I could finally solve the problem.

Seeing as it was a headache for me to solve this, I assume other newbies like me will have a hard time too, getting around this, so I will leave a well-documented approach to definitely solving this problem from scratch.

Yes, I am aware that the repo from nobody guy already gives a lot of insight and library documentation. Nevertheless, it will be confusing for an nRF framework newbie. For example, where you have to add the code to the board.overlay file, I had a hard time knowing what it was and understanding how to use it.

So firstly, to use the HX711, its library has to be installed. This library can be gotten from nobody guy by doing the following;

Ensure your IDE is adequately installed because lacking components might cause problems. Nordic does a great job at explaining how to do this with their course.

After installation, create a simple project from the project templates. The hello world project will do. You can also see what they have done in the course.

 

NB: Make sure you are choosing the right locations for your project, SDK and Toolchain installation.

After creating a new project, add a new build for the project.
 

 

NB: Make sure you are choosing the right settings for your board. If you are using the nRF9160DK, you can just use the above settings.

After adding the build configurations, build your project.
 

After building your project, the next thing will be to install your libraries.

Close your IDE and go to your installation folder, then open the SDK folder. For me, the path is something like "C:\ncs\v2.2.0\".

In your installation folder open the ".west" folder.

In your ".west" open the "config" file in a text editor. This will give you the location of your "west.yml" file.

 

As you can see, my "west.yml" file, is found in the "nrf" folder inside my installation folder. So, just go there and open it. My own path to that file will be something like "C:\ncs\v2.2.0\nrf\west.yml".


In the "west.yml" file, add the following specifications for the HX711 module;

- name: HX711
 path: modules/HX711
 revision: refs/tags/zephyr-v3.2.0
 url: https://github.com/nobodyguy/HX711_zephyr_driverCode

If you look under the "projects:" line, you will see a similar list of module specifications. You can just scroll till you reach the last module, indent from the margin to like the modules above and then add your specifications under them.

After adding your HX711 module you should have something like the image below;

 

After adding the module specifications, save your "west.yml" file and close it.

Open your "command prompt" app ("terminal" app for Linux and Mac).

Navigate to your "west.yml" file location in your command line app.

Since I am on windows, my location is something like "C:\ncs\v2.2.0\nrf" so I will just use the "cd" command to get into that location, as shown below.

 

In your command line app, once you are in this location, update the west module file "west.yml" you earlier modifies and saved. This will verify the specifications you earlier added then download all necessary components for the HX711 module from nobody guy's repo.

To update your "west.yml", make sure you are connected to the internet, then enter the command "west update" in your command line app. That will look something like the images below;

 

Once done, you should see your module file start updating, as below;

 

Then you should see that one of the modules updated is the HX711 module, as in the image below;

 

If you see that, it means your module has been successfully installed.

It happens sometimes that you get an error, as I did. That usually is because either "Python" or "West" is not installed on your PC.

Make sure that your "Python" and "West" are installed and up to date, especially "Python", because "West" is just actually a "Python" module and depends on "Python" to work.

Verify if "Python" is installed, by simply typing the "python --version" command, in your command line app. You should see your "Python" version, as shown below.

 

If your command line environment doesn't recognize "Python", it's probably because you are lacking python on your PC. Go to the Python website, and get instructions on how to install python for your operating system.

If python is installed, make sure you upgrade "PIP" to the latest version. you can use the "python -m pip install --upgrade pip" command, in your command line app.

NB: you may have to run your command line app with administrator privileges.

Verify if "West" is installed, by simply typing the "west --version" command, in your command line app. You should see your "West" version, as shown below.

 

If your command line environment doesn't recognize "West" it's probably because you are lacking the west module for python. Install the west module by typing the command "pip install west" in your command line app. As shown below;

 

If you earlier had trouble using the  "west update" command, after installing "Python" and "West", you can try the "west update" command. As you can see for me, "West" is already installed.

The next thing to do is to enable your sensor driver. To do that, open your IDE and launch your project. In your project file explorer, locate the "prj.conf" file and open it.

 

Add the following lines in your "prj.conf" file;

CONFIG_SENSOR=y
CONFIG_HX711=y
CONFIG_LOG=yCode

 

Once your file is modified, save it. Your project will automatically build to update the changes.

The next thing will be to define the HX711 and the pins it uses, in your overlay file. To do that, start by creating an overlay file, by clicking on "create" an overlay, which you most probably don't have by now.

Create by clicking on the "No overlay files Click to create one" option

 

Open the "overlay" file and add the following code as shown below;

/{
  hx711 {
 compatible = "avia,hx711";
 status = "okay";
 label = "HX711";
 dout-gpios = ;
 sck-gpios = ;
 // rate-gpios = ;
  };
};Code

 

So, if you have already checked the instructions on nobody guy's repo, you may see that my overlay code is slightly different.

I changed the pins of "dout-gpios" and "sck-gpios" to 2 (P0.02) and 3 (P0.03) respectively, because those pins also coincide with the nRF9160 onboard LEDs 1 and 2 respectively. This is so that if the code and hardware work properly, you should see the LEDs corresponding to these pins flash their lights.

I also commented the line for the "rate-gpios" pin, out, because as  Vidar Berg (vibe) , earlier said above, my HX711 doesn't provide room for that pin and it is not necessary in my case.

If your HX711 does support that pin, you will have to connect the "rate-pin" of your HX711 to pin 25 (P0.25) of your nRF9160 DK, as that is the dedicated pin for clock connections on the nRF9160 DK. If you are not using the nRF9160 DK like me, then you will have to check for your dedicated clock pin by looking at the back of your board, or by checking your board specifications on nordic's website.

 

The next thing will be to edit your "main.c" file;

 

Add the following code to your "main.c" file;

/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include 
#include 
#include 
#include 
#include 
#include 
#include 

#include 
#include 

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF...Code

Again, I have slightly modified the code from nobody guy's repo. This is because in the earlier overlay file, I had commented out the  "rate-gpios" pin, given that I was not going to use it. So, I removed all the code that was related to, or referenced the "rate-gpios" pin in the overlay file.

After adding the code, do a "Pristine Build" for your project, as shown below;

 

When your build is done, one important thing you MUST do else your project will not work, is to enable your microcontroller board to read VDD (3V) signal. By default, Nordic sets their boards to not to VDD(3V), but for your case you will need it, because as  Vidar Berg (vibe) earlier said, VCC of the HX711 board is connected to VDD of the nRF9160 DK board.

To enable VDD, locate the small switch button just beside your power switch button. If your board is new, you may see a dark-brownish thin plastic paper covering the VDD switch. remove the plastic then push the switch to VDD.

 

NB: Make sure your switch button is on the side of 3V as in the image above ELSE YOUR BOARD WILL NOT READ YOUR SENSOR DATA.

Once VDD is set, you can proceed with your connections. I did mine as follows;

Load sensor red-wire to HX711 E+ pin
Load sensor black-wire to HX711 E- pin
Load sensor white-wire to HX711 A- pin
Load sensor green-wire to HX711 A+ pin
HX711 VCC pin to nRF9160 VDD pin
HX711 SCK pin to nRF9160 P0.03 pin
HX711 DT pin to nRF9160 P0.02 pin
HX711 GND pin to nRF9160 GND pin

Once that is done, flash your board with your code;

 

Once your board is complete with flashing, connect to a COM PORT and check the nRF Terminal for readings;

 

I had set my calibration value to 1KG, because I had a know weight of 1KG. But you can change it to suite your known weight. Make sure during calibration, you put your weight on the load sensor, when you see the count down in your nRF terminal.

If you want to use the exact code I did, you can get my project from my repo. Since this is basically the code from no body guy's repo that I modified, I put the code in my repo under the same license (Apache-2.0 license) make sure you read the license before using the code.

I also have a colleague that worked on the SAADC method of using load sensors with nRF9160 DK, may also want to clone the repo and check it out.

HOPEFULLY THIS DEFINITELY SOLVES AND SEALS THIS PROBLEM.
