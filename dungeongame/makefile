all: rpg

Player.o: Player.c
	gcc -c Player.c

Game.o: Game.c
	gcc -c Game.c

Lab08_main.o: Lab08_main.c
	gcc -c Lab08_main.c

rpg: Player.o Game.o Lab08_main.o
	gcc -Wall Player.o Game.o Lab08_main.o -o rpg

clean:
	rm Player.o Game.o Lab08_main.o rpg