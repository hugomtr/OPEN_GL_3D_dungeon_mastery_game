#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>

struct Sound {
    sf::Sound sound;
    sf::SoundBuffer buffer_music;
    bool music_played = false;

    Sound();

    Sound(const char * path){
        if (!buffer_music.loadFromFile(path))
            std::cout << "Error loading sound file at path : " << path << std::endl;

        sound.setBuffer(buffer_music);
    }

    void loop(){
        sound.setLoop(true);
    }

    void play(){
        music_played = true;
        sound.play();
    }

    void stop(){
        music_played = false;
        sound.stop();
    }

};

#endif

