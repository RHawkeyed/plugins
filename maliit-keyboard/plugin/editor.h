/*
 * This file is part of Maliit Plugins
 *
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Copyright (C) 2012-2013 Canonical Ltd
 *
 * Contact: Mohammad Anwari <Mohammad.Anwari@nokia.com>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * Neither the name of Nokia Corporation nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef MALIIT_KEYBOARD_EDITOR_H
#define MALIIT_KEYBOARD_EDITOR_H

#include "models/key.h"
#include "models/wordcandidate.h"
#include "logic/abstracttexteditor.h"

#include <maliit/plugins/abstractinputmethodhost.h>
#include <QtCore>

#include "common.h"

namespace MaliitKeyboard {

class MALIIT_KEYBOARD_PLUGIN_LIBRARY Editor
    : public Logic::AbstractTextEditor
{
    Q_OBJECT
    Q_DISABLE_COPY(Editor)

private:
    MAbstractInputMethodHost *m_host;

public:
    explicit Editor(Model::Text *text,
                    Logic::AbstractWordEngine *word_engine,
                    Logic::AbstractLanguageFeatures *language_features,
                    QObject *parent = 0);
    virtual ~Editor();

    void setHost(MAbstractInputMethodHost *host);

private:
    //! \reimp
    virtual void sendPreeditString(const QString &preedit,
                                   Model::Text::PreeditFace face,
                                   const Replacement &replacement);
    virtual void sendCommitString(const QString &commit);
    virtual void sendKeyEvent(KeyState state,
                              Qt::Key key,
                              Qt::KeyboardModifier modifier);
    virtual void invokeAction(const QString &action,
                              const QString &key_sequence);
    //! \reimp_end
};

} // namespace MaliitKeyboard

#endif // MALIIT_KEYBOARD_EDITOR_H
