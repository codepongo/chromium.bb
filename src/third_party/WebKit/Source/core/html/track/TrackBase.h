/*
 * Copyright (C) 2011 Apple Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TrackBase_h
#define TrackBase_h

#include "platform/heap/Handle.h"
#include "wtf/RefCounted.h"
#include "wtf/text/AtomicString.h"

namespace WebCore {

class TrackBase : public RefCountedWillBeRefCountedGarbageCollected<TrackBase> {
public:
    virtual ~TrackBase();

    enum Type { TextTrack, AudioTrack, VideoTrack };
    Type type() const { return m_type; }

    const AtomicString& kind() const { return m_kind; }
    virtual void setKind(const AtomicString&);

    AtomicString label() const { return m_label; }
    void setLabel(const AtomicString& label) { m_label = label; }

    AtomicString language() const { return m_language; }
    void setLanguage(const AtomicString& language) { m_language = language; }

    AtomicString id() const { return m_id; }
    void setId(const AtomicString& id) { m_id = id; }

    virtual void trace(Visitor*) { }

protected:
    TrackBase(Type, const AtomicString& label, const AtomicString& language, const AtomicString& id);

    virtual bool isValidKind(const AtomicString&) const = 0;
    virtual AtomicString defaultKind() const = 0;

private:
    Type m_type;
    AtomicString m_kind;
    AtomicString m_label;
    AtomicString m_language;
    AtomicString m_id;
};

} // namespace WebCore

#endif // TrackBase_h
