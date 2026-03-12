#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
        char *title;
        char *artist;
        char *genre;
        float duration;
} Song;


int main(int argc, char *argv[]) {
        if (argc != 2) {
                printf("Error: No input file specified. Please provide the input file via a command-line argument.\n");
                return 1;
        }

        FILE *fp = fopen(argv[1], "r");

        if(fp == NULL){
        printf("Error: No input file specified. Plaese provide the input file via a command-line argument.\n");
        return 1;
        }

        int n;
        fscanf(fp, "%d", &n);

        Song *playlist = (Song *)malloc(n*sizeof(Song));

        if(playlist == NULL){
        return 1;
        }
	
	for(int i=0;i<n;i++){
		playlist[i].title = (char*)malloc(30*sizeof(char));
		playlist[i].artist = (char*)malloc(30*sizeof(char));
		playlist[i].genre = (char*)malloc(30*sizeof(char));
	}


        for(int i=0; i<n ; i++){
                fscanf(fp, "%s %s %s %f", playlist[i].title, playlist[i].artist, playlist[i].genre, &playlist[i].duration);
        }

        fclose(fp);

        printf("Total songs in the playlist: %d\n\n", n);

        for(int i=0;i<n;i++){
                printf("%d. %s by %s\n", i+1, playlist[i].title, playlist[i].artist);
                printf("   Genre: %s, Duration: %.2f minutes\n\n", playlist[i].genre, playlist[i].duration);
        }

	for(int i=0;i<n;i++){
                free(playlist[i].title);
                free(playlist[i].artist);
                free(playlist[i].genre);
        }

        free(playlist);

        return 0;
}
