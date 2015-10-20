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

#ifndef MALIIT_KEYBOARD_INPUTMETHOD_H
#define MALIIT_KEYBOARD_INPUTMETHOD_H

#include <maliit/plugins/abstractinputmethod.h>
#include <maliit/plugins/abstractinputmethodhost.h>
#include <maliit/plugins/keyoverride.h>
#include <QtGui>

#include "common.h"

namespace MaliitKeyboard {

class InputMethodPrivate;

class MALIIT_KEYBOARD_PLUGIN_LIBRARY InputMethod
    : public MAbstractInputMethod
{
    Q_OBJECT
    Q_DISABLE_COPY(InputMethod)
    Q_DECLARE_PRIVATE(InputMethod)

public:
    explicit InputMethod(MAbstractInputMethodHost *host);
    virtual ~InputMethod();

    //! \reimp
    virtual void show();
    Q_SLOT virtual void hide();
    virtual void setPreedit(const QString &preedit,
                            int cursor_position);
    virtual void switchContext(Maliit::SwitchDirection direction,
                               bool animated);
    virtual QList<MAbstractInputMethod::MInputMethodSubView>
    subViews(Maliit::HandlerState state = Maliit::OnScreen) const;
    virtual void setActiveSubView(const QString &id,
                                  Maliit::HandlerState state = Maliit::OnScreen);
    virtual QString activeSubView(Maliit::HandlerState state = Maliit::OnScreen) const;
    virtual void handleAppOrientationChanged(int angle);
    virtual bool imExtensionEvent(MImExtensionEvent *event);
    virtual void setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides);
    //! \reimp_end

    Q_SLOT void onLeftLayoutSelected();
    Q_SLOT void onRightLayoutSelected();

private:
    void registerStyleSetting(MAbstractInputMethodHost *host);
    void registerFeedbackSetting(MAbstractInputMethodHost *host);
    void registerAutoCorrectSetting(MAbstractInputMethodHost *host);
    void registerAutoCapsSetting(MAbstractInputMethodHost *host);
    void registerWordEngineSetting(MAbstractInputMethodHost *host);
    void registerHideWordRibbonInPortraitModeSetting(MAbstractInputMethodHost *host);
    void registerAutoRepeatBehaviour(MAbstractInputMethodHost *host);

    Q_SLOT void onScreenSizeChange(const QRect &rect);
    Q_SLOT void onStyleSettingChanged();
    Q_SLOT void onKeyboardClosed();
    Q_SLOT void onFeedbackSettingChanged();
    Q_SLOT void onAutoCorrectSettingChanged();
    Q_SLOT void onAutoCapsSettingChanged();
    Q_SLOT void onWordEngineSettingChanged();
    Q_SLOT void onHideWordRibbonInPortraitModeSettingChanged();
    Q_SLOT void onAutoRepeatBehaviourChanged();
    Q_SLOT void updateKey(const QString &key_id,
                          const MKeyOverride::KeyOverrideAttributes changed_attributes);

    Q_SLOT void onLayoutWidthChanged(int width);
    Q_SLOT void onLayoutHeightChanged(int height);
    Q_SLOT void onExtendedLayoutWidthChanged(int width);
    Q_SLOT void onExtendedLayoutHeightChanged(int height);
    Q_SLOT void onExtendedLayoutOriginChanged(const QPoint &origin);
    Q_SLOT void onMagnifierLayoutWidthChanged(int width);
    Q_SLOT void onMagnifierLayoutHeightChanged(int height);
    Q_SLOT void onMagnifierLayoutOriginChanged(const QPoint &origin);

    const QScopedPointer<InputMethodPrivate> d_ptr;
};

} // namespace MaliitKeyboard

#endif // MALIIT_KEYBOARD_INPUTMETHOD_H
