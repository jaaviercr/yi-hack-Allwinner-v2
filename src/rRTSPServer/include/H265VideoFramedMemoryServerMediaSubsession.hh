/*
 * Copyright (c) 2024 roleo.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * A ServerMediaSubsession object that creates new, unicast, RTPSink
 * on demand, from a H264 Elementary Stream video memory.
 */

#ifndef _H265_VIDEO_FRAMED_MEMORY_SERVER_MEDIA_SUBSESSION_HH
#define _H265_VIDEO_FRAMED_MEMORY_SERVER_MEDIA_SUBSESSION_HH

#include "OnDemandServerMediaSubsession.hh"

#include "rRTSPServer.h"

class H265VideoFramedMemoryServerMediaSubsession: public OnDemandServerMediaSubsession {
public:
    static H265VideoFramedMemoryServerMediaSubsession*
        createNew(UsageEnvironment& env, cb_output_buffer *cbBuffer,
                                Boolean reuseFirstSource);

    // Used to implement "getAuxSDPLine()":
    void checkForAuxSDPLine1();
    void afterPlayingDummy1();

protected:
    H265VideoFramedMemoryServerMediaSubsession(UsageEnvironment& env,
                                        cb_output_buffer *cbBuffer,
                                        Boolean reuseFirstSource);
      // called only by createNew();
      virtual ~H265VideoFramedMemoryServerMediaSubsession();

      void setDoneFlag() { fDoneFlag = ~0; }

protected: // redefined virtual functions
    virtual char const* getAuxSDPLine(RTPSink* rtpSink,
                                    FramedSource* inputSource);
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
                                              unsigned& estBitrate);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
                                    FramedSource* inputSource);

private:
    cb_output_buffer *fBuffer;
    char* fAuxSDPLine;
    char fDoneFlag; // used when setting up "fAuxSDPLine"
    RTPSink* fDummyRTPSink; // ditto
};

#endif
