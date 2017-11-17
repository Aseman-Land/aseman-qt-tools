/*
    Copyright (C) 2017 Aseman Team
    http://aseman.co

    AsemanQtTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AsemanQtTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "asemanaudiorecorder.h"
#include "asemanaudioencodersettings.h"

#include <QAudioRecorder>
#include <QPointer>
#include <QDebug>

class AsemanAudioRecorderPrivate
{
public:
    QPointer<AsemanAudioEncoderSettings> encoderSettings;
    QAudioRecorder *recorder;
};

AsemanAudioRecorder::AsemanAudioRecorder(QObject *parent) :
    QObject(parent)
{
    p = new AsemanAudioRecorderPrivate;
    p->recorder = new QAudioRecorder(this);

    connect(p->recorder, SIGNAL(stateChanged(QMediaRecorder::State)),
            SIGNAL(stateChanged()));
    connect(p->recorder, SIGNAL(statusChanged(QMediaRecorder::Status)),
            SIGNAL(statusChanged()));
    connect(p->recorder, SIGNAL(availabilityChanged(bool)), SIGNAL(availableChanged()));
    connect(p->recorder, SIGNAL(mutedChanged(bool)), SIGNAL(muteChanged()));
    connect(p->recorder, SIGNAL(volumeChanged(qreal)), SIGNAL(volumeChanged()));
    connect(p->recorder, SIGNAL(availabilityChanged(QMultimedia::AvailabilityStatus)),
            SIGNAL(availabilityChanged()));
}

AsemanAudioEncoderSettings *AsemanAudioRecorder::encoderSettings() const
{
    return p->encoderSettings;
}

void AsemanAudioRecorder::setEncoderSettings(AsemanAudioEncoderSettings *settings)
{
    if(p->encoderSettings == settings)
        return;

    p->encoderSettings = settings;
    emit encoderSettingsChanged();
}

void AsemanAudioRecorder::setOutput(const QUrl &url)
{
    if(p->recorder->outputLocation() == url)
        return;

    p->recorder->setOutputLocation(url);
    emit outputChanged();
}

QUrl AsemanAudioRecorder::output() const
{
    return p->recorder->outputLocation();
}

bool AsemanAudioRecorder::mute() const
{
    return p->recorder->isMuted();
}

void AsemanAudioRecorder::setMute(bool stt)
{
    if(p->recorder->isMuted() == stt)
        return;

    p->recorder->setMuted(stt);
}

qreal AsemanAudioRecorder::volume() const
{
    return p->recorder->volume();
}

void AsemanAudioRecorder::setVolume(qreal vol)
{
    if(p->recorder->volume() == vol)
        return;

    p->recorder->setVolume(vol);
}

void AsemanAudioRecorder::setAudioInput(const QString &input)
{
    if(p->recorder->audioInput() == input)
        return;

    p->recorder->setAudioInput(input);
    emit audioInputChanged();
}

QString AsemanAudioRecorder::audioInput() const
{
    return p->recorder->audioInput();
}

QStringList AsemanAudioRecorder::audioInputs() const
{
    return p->recorder->audioInputs();
}

bool AsemanAudioRecorder::available() const
{
    return p->recorder->isAvailable();
}

int AsemanAudioRecorder::availability() const
{
    return p->recorder->availability();
}

int AsemanAudioRecorder::state() const
{
    return p->recorder->state();
}

int AsemanAudioRecorder::status() const
{
    return p->recorder->status();
}

void AsemanAudioRecorder::stop()
{
    p->recorder->stop();
}

void AsemanAudioRecorder::pause()
{
    p->recorder->pause();
}

void AsemanAudioRecorder::record()
{
    p->recorder->setEncodingSettings( p->encoderSettings? p->encoderSettings->exportSettings() : QAudioEncoderSettings() );
    p->recorder->record();
}

AsemanAudioRecorder::~AsemanAudioRecorder()
{
    delete p;
}
