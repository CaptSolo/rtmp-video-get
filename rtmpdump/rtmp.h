#ifndef __RTMP_H__
#define __RTMP_H__
/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *      Copyright (C) 2008-2009 Andrej Stepanchuk
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RTMPDumper; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#include "AMFObject.h"
#include "rtmppacket.h"

namespace RTMP_LIB
{

typedef struct
{
        char hostname[256];
        unsigned int port;

        char *url;
        char *tcUrl;
        char *player;
        char *pageUrl;
        char *app;
        char *auth;
	char *flashVer;

	double seekTime;
} LNK;

class CRTMP
  {
    public:

      CRTMP();
      virtual ~CRTMP();

      //void SetPlayer(const std::string &strPlayer);
      //void SetPageUrl(const std::string &strPageUrl);
      //void SetPlayPath(const std::string &strPlayPath);
      void SetBufferMS(int size);
      void UpdateBufferMS();

      bool Connect(char *url, char *tcUrl, char *player, char *pageUrl, char *app, char *auth, char *flashVer, double dTime);
      bool IsConnected(); 
      double GetDuration();

      bool GetNextMediaPacket(RTMPPacket &packet);

      void Close();

      static int EncodeString(char *output, const std::string &strValue);
      static int EncodeNumber(char *output, double dVal);
      static int EncodeInt16(char *output, short nVal);
      static int EncodeInt24(char *output, int nVal);
      static int EncodeInt32(char *output, int nVal);
      static int EncodeBoolean(char *output,bool bVal);

      static short ReadInt16(const char *data);
      static int  ReadInt24(const char *data);
      static int  ReadInt32(const char *data);
      static std::string ReadString(const char *data);
      static bool ReadBool(const char *data);
      static double ReadNumber(const char *data);

      static bool FindFirstMatchingProperty(AMFObject &obj, std::string name, AMFObjectProperty &p);

    protected:
      bool HandShake();
      bool Connect();

      bool SendConnectPacket();
      bool SendServerBW();
      bool SendCheckBW();
      bool SendCheckBWResult();
      bool SendPing(short nType, unsigned int nObject, unsigned int nTime = 0);
      bool SendCreateStream(double dStreamId);
      bool SendPlay();
      bool SendPause();
      bool SendSeek(double dTime);
      bool SendBytesReceived();

      void HandleInvoke(const RTMPPacket &packet);
      void HandleMetadata(char *body, unsigned int len);
      void HandleChangeChunkSize(const RTMPPacket &packet);
      void HandleAudio(const RTMPPacket &packet);
      void HandleVideo(const RTMPPacket &packet);
      void HandlePing(const RTMPPacket &packet);
     
      int EncodeString(char *output, const std::string &strName, const std::string &strValue);
      int EncodeNumber(char *output, const std::string &strName, double dVal);
      int EncodeBoolean(char *output, const std::string &strName, bool bVal);

      bool SendRTMP(RTMPPacket &packet);

      bool ReadPacket(RTMPPacket &packet);
      int  ReadN(char *buffer, int n);
      bool WriteN(const char *buffer, int n);

      bool FillBuffer();

      int  m_socket;
      int  m_chunkSize;
      int  m_nBWCheckCounter;
      int  m_nBytesIn;
      int  m_nBytesInSent;
      bool m_bPlaying;
      int  m_nBufferMS;

      //std::string m_strPlayer;
      //std::string m_strPageUrl;
      //std::string m_strLink;
      //std::string m_strPlayPath;

      std::vector<std::string> m_methodCalls; //remote method calls queue

      LNK Link;
      char *m_pBuffer;
      int  m_nBufferSize;
      RTMPPacket m_vecChannelsIn[64];
      RTMPPacket m_vecChannelsOut[64];

      double m_fDuration; // duration of stream in seconds
  };
};

#endif


