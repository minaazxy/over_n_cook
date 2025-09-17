## How to Start

### WebGL

1. Go to the top-right corner of this repository and click **Code → Download ZIP**.  
2. Unzip the file, then open the folder in **VSCode**.  
3. In the VSCode terminal, run:

   ```bash
   docker compose up
   ```

Alternatively, if you are familiar with **Git**, you can quickly set up the game and the C++ server using:

   ```bash
   git clone https://github.com/iceylemon157/sprout-c-game-2024
   cd sprout-c-game-2024
   docker compose up
   ```

Once the setup is complete, open your browser and go to:

```
http://localhost:12345/app
```

You should now see the game running.

---

### C++ Server

To start the C++ server:

1. Open a **new terminal**.  
2. Navigate into the `sprout-c-game-2024` folder (the folder you just downloaded or cloned).  
3. Run the following commands:

   ```bash
   docker compose exec cpp_server /bin/bash
   # Inside the Docker container:
   make && ./server
   ```

This will compile and launch the C++ server inside the Docker container.

---

## Reference

- Game assets are mostly from the tutorial by [Code Monkey](https://www.youtube.com/watch?v=AmGSEH7QcDg).  
- Many of the C# scripts (for the WebGL build) are also adapted from the tutorial, but have been modified to work with the C++ server.

---

## Prerequisites

- [Docker](https://www.docker.com/get-started) installed on your machine  
- [VSCode](https://code.visualstudio.com/) (recommended for editing and running commands)  
- (Optional) [Git](https://git-scm.com/) if you want to clone the repository instead of downloading the ZIP

---

## License

This project is for educational purposes only. Game assets and tutorials belong to their respective creators.


___


I'm currently woring on the multiplayer mode.
If you just want to play, just download the Docker Engine and the .html file. 

