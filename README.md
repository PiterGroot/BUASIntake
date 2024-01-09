## BUASIntake: EcoClean Adventure

### Important code quick access:
Main.cpp [here](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Main.cpp)\
Gameobject base [here](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Framework/GameObject.cpp)\
GLSL background shader [here](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Resources/Shader/water_shader.frag)\
Player-related code logic [here](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Gameplay/PlayerBoat.cpp)\
General game-related code logic [here](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Game.cpp)\
Collision-related code logic: 
[AABB detection](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Framework/Collider.cpp)
[CollisionManager](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Managers/CollisionManager.cpp)

Important managers:
[Audio manager](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Managers/AudioManager.cpp)
[Text Label manager](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Managers/TextManager.cpp)
[Input manager](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Managers/InputManager.cpp)\
Other systems:
[Enemy spawner](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Systems/EnemySpawner.cpp)
[Pickup scatter](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Systems/PickupScatter.cpp)
[Start screens](https://github.com/PiterGroot/BUASIntake/blob/main/BUASIntake/Scripts/Systems/StartScreens.cpp)

### Game description:
In this game, you (the player) are tasked to clean up the environment. Navigate your boat to locate and collect floating plastic, garbage, and other waste. What is your ultimate goal? Clean the whole lake!

But beware, the polluted waters are not the only challenge you'll face. Menacing enemies, such as the formidable Kraken and treacherous Vortex, lurk beneath the surface. Avoid these threats to ensure a successful cleanup mission. 

Manage your resources wisely, as running out of fuel means game over. To replenish your fuel, deposit the collected waste on your home island. Receive power-ups to become more effective in your aid to clean up the lake.

### Controls:

Advance intro screens: "Space bar"

Movement: "WASD" keys\
Clean up: "Space bar" (when floating above waste)\
Escape Kraken: Rapidly press "E" key (consumes fuel!)\
Deposit Waste: Return to home island and press "E"
