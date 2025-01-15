#include  <Sound.h>
#include <QDebug>

Sound::Sound(QObject *parent)
	: QObject(parent)
{
	sound_mic_init();
	sound_play_init();
}

void Sound::sound_mic_init()
{
	int err;
	int dir = 0;
	snd_pcm_uframes_t frames = 320;
	unsigned rate = 8000;
	const char* device = "plughw:1";
	
	if ((err = snd_pcm_open(&handle_mic, device, SND_PCM_STREAM_CAPTURE, 0)) < 0)
	{
		qDebug() << "mic open error!";
	}
	else
	{
		qDebug() << "mic open!";
	
	
		if ((err = snd_pcm_hw_params_malloc(&hwparams)) < 0)
		{
			qDebug() << "hwparams malloc error!";
		}
		else
			qDebug() << "hwparams malloc!";
		if ((err = snd_pcm_hw_params_any(handle_mic, hwparams)) < 0)
		{
			qDebug() << "hwparams struct error!";
		}
		else
			qDebug() << "hwparams struct!";
		if ((err = snd_pcm_hw_params_set_access(handle_mic, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
		{
			qDebug() << "hwparams set access error!";
		}
		else
			qDebug() << "hwparams set access!";
		if ((err = snd_pcm_hw_params_set_format(handle_mic, hwparams, SND_PCM_FORMAT_S16_LE)) < 0)
		{
			qDebug() << "hwparams format error!";
		}
		else
			qDebug() << "hwparams format!";
		if ((err = snd_pcm_hw_params_set_rate_near(handle_mic, hwparams, &rate, 0)) < 0)
		{
			qDebug() << "hwparams rate error!";
		}
		else
			qDebug() << "hwparams rate!";
		if ((err = snd_pcm_hw_params_set_channels(handle_mic, hwparams, 1)) < 0)
		{
			qDebug() << "hwparams channels error!";
		}
		else
			qDebug() << "hwparams channels!";

		//snd_pcm_hw_params_set_periods(handle_mic, hwparams, frames, dir);

		if ((err = snd_pcm_hw_params(handle_mic, hwparams)) < 0)
		{
			qDebug() << "hwparams error!";
		}
		else
			qDebug() << "hwparams !";
		if ((err = snd_pcm_prepare(handle_mic)) < 0)
		{
			qDebug() << "prepare error!";
		}
		else
			qDebug() << "prepare!";
	
		mic_buffer = (unsigned char*)malloc(640);
		memset(mic_buffer, 0, 640);
	
		if (mic_buffer)
			qDebug() << "mic buffer ok!";
	}
}


void Sound::sound_play_init()
{
	int err;
	const char* device = "plughw:0,0";
	if ((err = snd_pcm_open(&handle_play, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		qDebug() << "playback open error!";
	}
	else
		qDebug() << "playback open!";
	if ((err = snd_pcm_set_params( handle_play,
		SND_PCM_FORMAT_S16_LE,
		SND_PCM_ACCESS_RW_INTERLEAVED,
		1,
		8000,
		1,
		500000)) < 0) 
	{
		qDebug() << "cannot set params";
	}
	else
		qDebug() << "set params!";
}
