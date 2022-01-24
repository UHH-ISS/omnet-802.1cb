//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef FRER_LATENTERRORDETECTION_H_
#define FRER_LATENTERRORDETECTION_H_

#include "core4inet/base/CoRE4INET_Defs.h"
#include "StreamIdentification.h"


struct ErrorDetectionWindow {
    int maxSeqNumber;
    std::vector<int> window;

    ErrorDetectionWindow() {maxSeqNumber = 0;};
    ErrorDetectionWindow(int ws) {maxSeqNumber = 0; for(unsigned int i = 0; i < ws; i++) window.push_back(0);};
    ErrorDetectionWindow(int ws, int sn) {maxSeqNumber = sn; for(unsigned int i = 0; i < ws; i++) window.push_back(0);};

    void operator=(const ErrorDetectionWindow &edw ) {
        maxSeqNumber = edw.maxSeqNumber;
        window = edw.window;
     };
};

typedef std::map<L2Identifier, ErrorDetectionWindow> ErrorDetectionTable;

class LatentErrorDetection : public cSimpleModule {
public:
    LatentErrorDetection();
    virtual ~LatentErrorDetection();

    void updateStreamSequence(L2Identifier, int);

protected:
    int sequenceWindowSize;
    int splitFactor;

    ErrorDetectionTable errorDetTable;

    void initialize() override;
    void finish() override;

private:
    simsignal_t receivedDuplicates;
};

#endif /* FRER_LATENTERRORDETECTION_H_ */
