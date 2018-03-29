// Scenario for user_app1//

Thread1
open ()- Acquires sem2 lock  and dev->count1 =1 . because mode1 is default mode 
sleep(8) - waits for 8 units of time
ioctl()- change of mode occurs without any interruption.


Thread2
sleep(3) - waits for 3 units of time
open()- count1 value is incremented and acquires sem2
ioctl()- gets stuck infinitely in the while loop as the count1 value is greater than 1

Thread3
sleep(5) - waits for 5 units of time
open() - increments the count1 value and waits to acquire sem2 with out proceeding further

THe above situation is a deadlock scenario.
where both threads are stuck in a infinite loop , thread 2 cannot come out of the loop because of the count1 value. 
Thread 3 get stuck at open().
user_app1 is used to test this scenario.


// Scenario for user_app2//

Thread1
open ()- Acquires sem2 lock  and dev->count1 =1 . because mode1 is default mode. 
sleep(10) - waits for 10 units of time without proceeding further
ioctl()- count1 is always greater than 1 as it is incremented by thread2 so, the while loop runs infinitely.


Thread2
sleep(3) - waits for 2 units of time
open()- increments the count1 value and waits to acquire sem2 with out proceeding further

Thread3
sleep(5) - waits for 4 units of time
open() - increments the count1 value and waits to acquire sem2 with out proceeding further

THe above situation is a deadlock scenario, 
where thread 1 gets stuck in the loop because of the count1 value and thread2 and thread 3 get stuck at opening.
user_app2 is related to this scenario.

// Scenario for user_app3//

Thread1
open ()- Acquires sem2 lock  and dev->count1 =1 . because mode1 is default mode. 
sleep(10) - waits for 10 units of time without proceeding further
write()- writes the given string succesfully.


Thread2
sleep(3) - waits for 3 units of time
open()- increments the count1 value and waits to acquire sem2 .
read()- read inevitably waits for write and finally reads the data in buffer.


THe above situation is a potential deadlock scenario, 
because the open in thread2 waits for thread1 to release sem2 but when thread1 is exited only after thread2 is executed which forms
a potential deadlock scenario but no deadlock is witnessed.
user_app3 is related to this scenario.

// Scenario for user_app4//

Thread1
open ()- Acquires sem2 lock  and dev->count1 =1 . because mode1 is default mode. 
sleep(10) - waits for 10 units of time without proceeding further
open()- tries to open in mode1 but cant because sem2 is already acquired.

Now this causes a deadlock scenario because the second open() tries to open but doesnt have sem2 , inorder to release sem2 ,
this open() should get completed which causes a deadlock.user_app4 is related to this scenario
