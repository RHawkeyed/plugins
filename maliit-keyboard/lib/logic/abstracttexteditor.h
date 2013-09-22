/*
 * This file is part of Maliit Plugins
 *
 * Copyright (C) 2012-2013 Canonical Ltd
 *
 * Contact: maliit-discuss@lists.maliit.org
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

#ifndef MALIIT_KEYBOARD_TEXTEDITOR_H
#define MALIIT_KEYBOARD_TEXTEDITOR_H

#include "models/key.h"
#include "models/wordcandidate.h"
#include "models/text.h"
#include "models/styleattributes.h"
#include "logic/abstractwordengine.h"
#include "logic/abstractlanguagefeatures.h"

#include <QtCore>

namespace MaliitKeyboard {
namespace Logic {

class EventHandler;
class LayoutUpdater;
class AbstractTextEditor;

void connectEventHandlerToTextEditor(EventHandler *event_handler,
                                     AbstractTextEditor *editor);

void connectLayoutUpdaterToTextEditor(LayoutUpdater *updater,
                                      AbstractTextEditor *editor);

class AbstractTextEditorPrivate;

class AbstractTextEditor
    : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractTextEditor)
    Q_DECLARE_PRIVATE(AbstractTextEditor)
    Q_PROPERTY(bool preeditEnabled READ isPreeditEnabled
                                   WRITE setPreeditEnabled
                                   NOTIFY preeditEnabledChanged)
    Q_PROPERTY(bool autoCorrectEnabled READ isAutoCorrectEnabled
                                       WRITE setAutoCorrectEnabled
                                       NOTIFY autoCorrectEnabledChanged)
    Q_PROPERTY(bool autoCapsEnabled READ isAutoCapsEnabled
                                    WRITE setAutoCapsEnabled
                                    NOTIFY autoCapsEnabledChanged)

public:
    struct Replacement
    {
        Replacement()
            : start(0)
            , length(0)
            , cursor_position(-1)
        {}

        Replacement(int position)
            : start(0)
            , length(0)
            , cursor_position(position)
        {}

        Replacement(int r_start,
                    int r_length,
                    int position)
            : start(r_start)
            , length(r_length)
            , cursor_position(position)
        {}

        int start;
        int length;
        int cursor_position;
    };

    enum KeyState {
        KeyStatePressed,
        KeyStateReleased
    };

    explicit AbstractTextEditor(Model::Text *text,
                                Logic::AbstractWordEngine *word_engine,
                                Logic::AbstractLanguageFeatures *language_features,
                                QObject *parent = 0);
    virtual ~AbstractTextEditor() = 0;

    Model::Text * text() const;
    Logic::AbstractWordEngine * wordEngine() const;
    Logic::AbstractLanguageFeatures * languageFeatures() const;

    void setAutoRepeatBehaviour(int auto_repeat_delay,
                                int auto_repeat_interval);

    Q_SLOT void onKeyPressed(const Key &key);
    Q_SLOT void onKeyReleased(const Key &key);
    Q_SLOT void onKeyEntered(const Key &key);
    Q_SLOT void onKeyExited(const Key &key);
    Q_SLOT void onCursorPositionChanged(int cursor_position,
                                        const QString &surrounding_text);
    Q_SLOT void replacePreedit(const QString &replacement);
    Q_SLOT void replaceAndCommitPreedit(const QString &replacement);
    Q_SLOT void clearPreedit();

    bool isPreeditEnabled() const;
    Q_SLOT void setPreeditEnabled(bool enabled);
    Q_SIGNAL void preeditEnabledChanged(bool enabled);

    bool isAutoCorrectEnabled() const;
    Q_SLOT void setAutoCorrectEnabled(bool enabled);
    Q_SIGNAL void autoCorrectEnabledChanged(bool enabled);

    bool isAutoCapsEnabled() const;
    Q_SLOT void setAutoCapsEnabled(bool enabled);
    Q_SIGNAL void autoCapsEnabledChanged(bool enabled);

    Q_SIGNAL void keyboardClosed();
    Q_SIGNAL void leftLayoutSelected();
    Q_SIGNAL void rightLayoutSelected();
    Q_SIGNAL void wordCandidatesChanged(const WordCandidateList &word_candidates);
    Q_SIGNAL void autoCapsActivated();

    Q_SLOT void showUserCandidate();
    Q_SLOT void addToUserDictionary(const QString &word);

private:
    const QScopedPointer<AbstractTextEditorPrivate> d_ptr;

    void sendPreeditString(const QString &preedit,
                           Model::Text::PreeditFace face);

    virtual void sendPreeditString(const QString &preedit,
                                   Model::Text::PreeditFace face,
                                   const Replacement &replacement) = 0;
    virtual void sendCommitString(const QString &commit) = 0;
    virtual void sendKeyEvent(KeyState state, Qt::Key key, Qt::KeyboardModifier modifier) = 0;
    virtual void invokeAction(const QString &action, const QString &key_sequence) = 0;

    void commitPreedit();
    Q_SLOT void autoRepeatBackspace();
};

}} // namespace Logic, MaliitKeyboard

#endif // MALIIT_KEYBOARD_ABSTRACTTEXTEDITOR_H
