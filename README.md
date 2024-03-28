Particle system assignment cs4360

Camera
- w,a,s,d,q,e forward, left, back, right, up, down relative to camera
- shift for walk mode
- scroll wheel to change velocity.

Controls
- 'r' to reset current affect
- space to switch between affects.

Notes on using my xml files
- I didnt add error checking so typos may lead to strange behavior.
- velocity spawn property is more so a direction where the speed of it will be the length of the min specified value.
(the value for constProp and min for randProp)
- Burst emitter bursts num_particles once its duration property reaches 0. Therefore spawn_rate property on burst emitter is redundant.


Not necessary to read below this point. Just thought I would explain how some of my implementations work.

Notes on how parser works
- ConstPropertyNodeReader and RandomPropertyNodeReader derive from common PropertyNodeReader class
- ConstPropertyNodeReader holds a ValueNodeReader and RandomPropertyNodeReader holds 2 ValueNodeReaders(min and max)
- ValueNodeReader is essentially a factory pattern to to create the correct type of PropertyValue Class to read in info for this xml node.
For example the float, vec3, vec4 etc. Wanted to do it this way to make is less hardcoded and more reusable.
- The PropertyValue class has these more specific classes inherit from it, and it holds their read in value in a generic T type.
- PropertyValue also inherits from an interface, IPropertyValue. This interface in not generic and can therfore be the type held by ValueNodeReader.
- PropertyNodeWrapper is simply a class to hold a ConstPropertyNodeReader and a RandomPropertyNodeReader, One of which is null.
I did this so the map of spawn properties could hold a PropertyNodeWrapper which could then be used to acces either a ConstPropertyNodeReader or a RandomPropertyNodeReader. The class PropertyNodeReader that they both already derive from could not be
used for this because it would need a pure virtual generic function getValue() which is not allowed. Only way around this I could think of
would be to dynamic cast every time it is accessed, which I believe would be worse than the approach I took.

Notes on signals
- Brief: signals are picked up in main and send to the reciever class to deal with them.
- The 2 samples I made both derive from Reciever and therefore register themselves to be able to recieve signals.
- Did this so that all signals(keyboard input) can be picked up in 1 place(main) and then the Reciever class
decides which recievers to send the signal to based on a predicate. The specific recievers decide how to deal
with this input themselves
- Only ended up having 1 type of signal to reset the effect.