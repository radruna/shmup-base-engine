/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-28
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream> //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list> //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../md5/md5.h" //Md5 hash thingy
#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "../graphics/imagehandler.h" //For loading images
#include "projectile.h" //Projectile header
#include "weapon.h" //Class def
#include "../sys/configreader.h" //Class def

namespace sbe
{
    Weapon::Weapon(const std::string& weaponFile, ImageHandler* imgHandler, ConfigReader* cfgReader, AudioHandler* audHandler)
    {
        firing = false;
        scriptFile = weaponFile;
        audioHandler = audHandler;
        imageHandler = imgHandler;
        configReader = cfgReader;
        load();
    }

    void Weapon::load()
    {
        std::ifstream fileReader;
        clear();

        Logger::writeMsg(1) << "\nLoading weapon " << scriptFile;

        //Open specified file
        fileReader.open(scriptFile.c_str());
        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Unable to open the specified weapon file";
            fileReader.close();
            return;
        }

        //Set default values
        name = "none";
        spriteName = "default_particle";

        shotsPerWave = 1;
        wavesPerAttack = 1;

        randEmissionAngle = false;

        pSystemFile = "none";
        sndKeyFiring = "none";
        sndKeyImpact = "none";

        emissionRate = 1;
        emissionAngleMin = -180;
        emissionAngleMax = 180;
        emissionForceMin = 0;
        emissionForceMax = 0;
        emissionFrictionMin = 1;
        emissionFrictionMax = 1;

        lifeSpanMin = 1;
        lifeSpanMax = 1;

        sizeMin = 1;
        sizeMax = 1;
        sizeRatio = 1;

        rotRateMin = 0;
        rotRateMax = 0;
        rotRandom = 0;
        rotAlign = 0;
        rotation = 0;

        fadeModifier.fadeInMin = 0;
        fadeModifier.fadeInMax = 0;
        fadeModifier.fadeInOffsetMin = 0;
        fadeModifier.fadeInOffsetMax = 0;
        fadeModifier.fadeOutMin = 0;
        fadeModifier.fadeOutMax = 0;

        sizeModifier.scalarRateMin = 1;
        sizeModifier.scalarRateMax = 1;
        sizeModifier.scalarRateOffset = 0;
        sizeModifier.oscFreqMin = 0;
        sizeModifier.oscFreqMax = 0;
        sizeModifier.oscAmpMin = 0;
        sizeModifier.oscAmpMax = 0;
        sizeModifier.oscAmpOffset = 0;

        emissionAngleModifier.scalarRateMin = 0;
        emissionAngleModifier.scalarRateMax = 0;
        emissionAngleModifier.oscFreqMin = 0;
        emissionAngleModifier.oscFreqMax = 0;
        emissionAngleModifier.oscAmpMin = 0;
        emissionAngleModifier.oscAmpMax = 0;
        emissionAngleModifier.oscAmpOffset = 0;

        movementAngleMin = 0;
        movementAngleMax = 0;

        alphaMin = 255;
        alphaMax = 255;
        alphaModifier.scalarRateMin = 0;
        alphaModifier.scalarRateMax = 0;

        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation
            if(strReadLine(output,parameterKey,parameterValue))
            {
                //Assign parameter value based on the type of parameter.
                //Generic parameters
                if(parameterKey == "name")
                    name = parameterValue;

                else if(parameterKey == "sprite_name")
                    spriteName = parameterValue;

                else if(parameterKey == "shots_per_wave")
                    shotsPerWave = atoi(parameterValue.c_str());
                else if(parameterKey == "waves_per_attack")
                    wavesPerAttack = atoi(parameterValue.c_str());
                else if(parameterKey == "waves_interval")
                    waveInterval = atof(parameterValue.c_str());

                else if(parameterKey == "emission_angle_random")
                    randEmissionAngle = (bool) atoi(parameterValue.c_str());//Convert string to bool

                else if(parameterKey == "particle_system")
                    pSystemFile = parameterValue;

                else if(parameterKey == "firing_sound")
                    sndKeyFiring = parameterValue;
                else if(parameterKey == "impact_sound")
                    sndKeyImpact = parameterValue;

                else if(parameterKey == "internal_oscillation")
                    internalOsc = (bool) atoi(parameterValue.c_str());//Convert string to bool

                //Emission parameters
                else if(parameterKey == "emission_rate")
                    emissionRate = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_min")
                    emissionAngleMin = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_angle_max")
                    emissionAngleMax = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_force_min")
                    emissionForceMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_force_max")
                    emissionForceMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_friction_min")
                    emissionFrictionMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_friction_max")
                    emissionFrictionMax = atof(parameterValue.c_str());//Convert string to float

                //Lifespan parameters
                else if(parameterKey == "lifespan_min")
                    lifeSpanMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "lifespan_max")
                    lifeSpanMax = atof(parameterValue.c_str());//Convert string to float

                //Size parameters
                else if(parameterKey == "size_min")
                    sizeMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_max")
                    sizeMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_ratio")
                    sizeRatio = atof(parameterValue.c_str());//Convert string to float

                //Rotation parameters
                else if(parameterKey == "rotation_rate_min")
                    rotRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "rotation_rate_max")
                    rotRateMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "rotation_random")
                    rotRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool
                else if(parameterKey == "rotation_align")
                    rotAlign = (bool) atoi(parameterValue.c_str());//Convert string to bool
                else if(parameterKey == "rotation")
                    rotation = atof(parameterValue.c_str());//Convert string to float

                //Fade parameters
                else if(parameterKey == "fade_in_min")
                    fadeModifier.fadeInMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_in_max")
                    fadeModifier.fadeInMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_in_offset_min")
                    fadeModifier.fadeInOffsetMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_in_offset_max")
                    fadeModifier.fadeInOffsetMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_out_min")
                    fadeModifier.fadeOutMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_out_max")
                    fadeModifier.fadeOutMax = atof(parameterValue.c_str());//Convert string to float

                //Size modification parameters
                else if(parameterKey == "size_mod_scalar_rate_min")
                    sizeModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_scalar_rate_max")
                    sizeModifier.scalarRateMax = atof(parameterValue.c_str());//Convert string to float

                else if(parameterKey == "size_mod_scalar_offset")
                    sizeModifier.scalarRateOffset = atof(parameterValue.c_str());//Convert string to float

                else if(parameterKey == "size_mod_oscillate_freq_min")
                    sizeModifier.oscFreqMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_freq_max")
                    sizeModifier.oscFreqMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_min")
                    sizeModifier.oscAmpMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_max")
                    sizeModifier.oscAmpMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_offset")
                    sizeModifier.oscAmpOffset = atof(parameterValue.c_str());//Convert string to float

                //Emission angle modification parameters
                else if(parameterKey == "emission_angle_mod_scalar_rate")                                           //Different!
                    emissionAngleModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_freq_min")
                    emissionAngleModifier.oscFreqMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_freq_max")
                    emissionAngleModifier.oscFreqMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_min")
                    emissionAngleModifier.oscAmpMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_max")
                    emissionAngleModifier.oscAmpMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_offset")
                    emissionAngleModifier.oscAmpOffset = atof(parameterValue.c_str());//Convert string to float

                //Movement parameters move_mod_angle_min
                else if(parameterKey == "move_mod_angle_min")
                    movementAngleMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "move_mod_angle_max")
                    movementAngleMax = atof(parameterValue.c_str());//Convert string to float

                //Alpha parameters
                else if(parameterKey == "alpha_min")
                    alphaMin = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "alpha_max")
                    alphaMax = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "alpha_mod_scalar_rate_min")
                    alphaModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "alpha_mod_scalar_rate_max")
                    alphaModifier.scalarRateMax = atof(parameterValue.c_str());//Convert string to float

                //Parameter not found
                else
                    Logger::writeMsg(1) << "Invalid weapon parameter: " << parameterKey;
            }
        }

        if(sndKeyFiring == "none")
        {}
        else
        {
            sndFiring = sf::Sound( audioHandler->getSound(sndKeyFiring) );
            sndFiring.SetVolume( audioHandler->getSFXVol() );
        }

        if(sndKeyImpact == "none")
        {}
        else
        {
            sndImpact = sf::Sound( audioHandler->getSound(sndKeyImpact) );
            sndImpact.SetVolume( audioHandler->getSFXVol() );
        }

        wavesLeft = 0;

        //No name parameter found in script file
        if(name == "none" || name == "")
            Logger::writeMsg(1) << "Weapon system needs a name!";

        //Set sprite to default particle if spriteName = empty
        if(spriteName == "")
            spriteName = "default_particle";

        //Debug output
        Logger::writeMsg(1) << "Finished!";
        //Close file
        fileReader.close();

        sprite = imageHandler->getImage(spriteName);

        age = 0;

        counter = 0;

    }

    void Weapon::Render(sf::RenderTarget& Target) const
    {
        //Draw projectiles
        for(std::list<Projectile>::const_iterator it = projectileList.begin(); it != projectileList.end(); it++) //Iterate through projectile list
        {
            Target.Draw(*it);
        }
    }

    void Weapon::startFiring()
    {
        if(!firing)
            counter = 1 / emissionRate;
        firing = true;
    }

    void Weapon::stopFiring()
    {
        firing = false;
    }

    //Remove all projectiles from system
    void Weapon::clear()
    {
        projectileList.clear();
    }

    void Weapon::SetPosition(float x, float y) //Set weapon
    {
        xPos = x;
        yPos = y;
    }

    float Weapon::GetPositionX()
    {
        return xPos;
    }

    float Weapon::GetPositionY()
    {
        return yPos;
    }


    void Weapon::Move(float x, float y) //Move weapon
    {
        xPos += x;
        yPos += y;
    }

    template<class T>
    T Weapon::boundsRand(T min, T max)
    {
        if(min > max) //Swap values if user = idiot
        {
            T temp = min;
            min = max;
            max = temp;
        }
        else if(min == max) //If same = one value
                return min;
            else //If different, value = random value between min and max
                return min + fmod(rand(), (max - min));

        return 0;
    }

    void Weapon::update(const float& elapsed)
    {
        //Increase age
        age += elapsed;

        if(firing)
            counter += elapsed; //Count time
        else
            counter = 0;

        //Emit new particle
        while(counter > 1 / emissionRate)
        {

            //Fire if firing == true
            if(firing || wavesLeft > 0)
            {

                //Get values and spawn projectile
                Particle::ParaMod sizeMod;
                Particle::ParaMod emissionAngleMod;

                //Get force
                float emissionForce = boundsRand( emissionForceMin , emissionForceMax );

                /*//Get rotation rate (divide by 10 for a nicer value)
                float rotRate = boundsRand( rotRateMin, rotRateMax ) / 10;
                //Get friction
                float emissionFriction = boundsRand( emissionFrictionMin , emissionFrictionMin );
                //Get lifespan
                float lifeSpan = boundsRand( lifeSpanMin , lifeSpanMax );
                //Get fade in duration
                float fadeInDur = boundsRand( fadeModifier.fadeInMin, fadeModifier.fadeInMax );
                //Get fade in offset
                float fadeInOffset = boundsRand( fadeModifier.fadeInOffsetMin, fadeModifier.fadeInOffsetMax );
                //Get fade out duration
                float fadeOutDur = boundsRand( fadeModifier.fadeOutMin, fadeModifier.fadeOutMax );
                //Get alpha
                int alpha = boundsRand( alphaMin, alphaMax );
                //Get movement mod
                float movementModAngle = boundsRand( movementAngleMin, movementAngleMax );*/

                //Get scalar size mod rate
                sizeMod.scalarRate = boundsRand( sizeModifier.scalarRateMin, sizeModifier.scalarRateMax );
                //Get scalar size mod offset
                sizeMod.scalarOffset = sizeModifier.scalarRateOffset;
                //Get oscillating size mod frequency
                sizeMod.frequency = boundsRand( sizeModifier.oscFreqMin, sizeModifier.oscFreqMax );
                //Get oscillating size mod amplitude
                sizeMod.amplitude = boundsRand( sizeModifier.oscAmpMin, sizeModifier.oscAmpMin );
                //Get oscillating size mod offset
                sizeMod.amplitudeOffset = sizeModifier.oscAmpOffset;

                //Get scalar emission angle mod rate
                emissionAngleMod.scalarRate = emissionAngleModifier.scalarRateMin;
                //Get oscillating emission angle mod frequency
                emissionAngleMod.frequency = boundsRand( emissionAngleModifier.oscFreqMin, emissionAngleModifier.oscFreqMax );
                //Get oscillating emission angle mod amplitude
                emissionAngleMod.amplitude = boundsRand( emissionAngleModifier.oscAmpMin, emissionAngleModifier.oscAmpMin );
                //Get oscillating emission angle mod offset
                emissionAngleMod.amplitudeOffset = emissionAngleModifier.oscAmpOffset;

                for(int i = 0;i < shotsPerWave; i++){

                    //emissionAngle = boundsRand( emissionAngleMin , emissionAngleMax );
                    float scale = boundsRand( sizeMin , sizeMax );

                    if(!randEmissionAngle && shotsPerWave != 1)
                        emissionAngle = emissionAngleMin + (emissionAngleMax - emissionAngleMin) / (shotsPerWave - 1) * i;
                    else if(!randEmissionAngle)
                        emissionAngle = emissionAngleMin + (emissionAngleMax - emissionAngleMin) / 2;
                    else
                        emissionAngle = boundsRand( emissionAngleMin , emissionAngleMax );

                    //Fire new projectile
                    projectileList.push_back( Projectile(imageHandler, configReader, xPos, yPos, sprite, emissionAngle, emissionForce, pSystemFile ));
                    //Handle size/ratio
                    projectileList.back().SetScale(scale, scale * sizeRatio);

                    if(sndKeyFiring == "none")
                    {}
                    else
                        sndFiring.Play();

                    if(elapsed > 1 / emissionRate)  //If time == shit
                        projectileList.back().push( emissionForce * counter);

                    //Handle rotation
                    if(rotAlign) //Should I align to emission angle?
                        projectileList.back().SetRotation( (emissionAngle * -1) + rotation ); //If yes, then do so + rotation
                    else if(rotRandom) //Should I start out with random rotation?
                        projectileList.back().SetRotation( rand() % 360 );
                    else //Just spawn with rotation
                        projectileList.back().SetRotation( rotation );

                }

                if(wavesLeft > 0)
                    wavesLeft--;
                else
                    wavesLeft = wavesPerAttack;

            }

            counter -=  1 / emissionRate;
        }

        for(std::list<Projectile>::iterator pIt = projectileList.begin(); pIt != projectileList.end(); pIt++) //Iterate through projectile list
        {
                pIt->update(elapsed); //Update projectile
                if( pIt->isUseless() )
                {
                    pIt->kill();
                    pIt = projectileList.erase(pIt); //Erase projectile
                    if(sndKeyImpact == "none")
                    {}
                    else
                        sndImpact.Play();
                }
        }

        xPosOld = GetPositionX();
        yPosOld = GetPositionY();

    }

}
