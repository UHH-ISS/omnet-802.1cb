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

#include "LatentErrorDetection.h"

LatentErrorDetection::LatentErrorDetection() {
    // TODO Auto-generated constructor stub

}

LatentErrorDetection::~LatentErrorDetection() {
    // TODO Auto-generated destructor stub
}

Define_Module(LatentErrorDetection);

void LatentErrorDetection::initialize() {
    splitFactor = par("splitFactor");
    sequenceWindowSize = par("sequenceWindowSize");

    //expectedPacketCount = registerSignal("expectedPacketCount");
    receivedDuplicates = registerSignal("receivedDuplicates");
}

void LatentErrorDetection::updateStreamSequence(L2Identifier key, int seqNumber) {

    auto it = errorDetTable.find(key);

    if(it != errorDetTable.end()) {
        int diff = errorDetTable[key].maxSeqNumber - seqNumber;

        // an obsolute packet
        if(diff > sequenceWindowSize) {
            std::cout << "Out of sequence window size" << endl;
            return;
        }

        // In window scope
        if(diff >= 0) {
            (errorDetTable[key].window)[sequenceWindowSize - 1 - diff]++;
        } else {
            // pivot (maxSeqNumber) pointing the last element of vector
            std::vector<int> newWindow;

            int remaining_entries = sequenceWindowSize + diff; // diff is negative

            if(-diff >= sequenceWindowSize)
                remaining_entries = 0;

            for(unsigned int i = 0; i < -diff; i++) {
                //emit(expectedPacketCount, splitFactor);
                emit(receivedDuplicates, (errorDetTable[key].window)[i]);
            }

            for(unsigned int i = 0; i < remaining_entries; i++)
                newWindow.push_back((errorDetTable[key].window)[i - diff]);

            for(unsigned int i = 0; i < -diff; i++)
                newWindow.push_back(0);

            newWindow[sequenceWindowSize - 1]++;

            errorDetTable[key].window = newWindow;
            errorDetTable[key].maxSeqNumber = seqNumber;
        }

        for(unsigned int i = 0; i < sequenceWindowSize; i++) {
            if((errorDetTable[key].window)[i] > splitFactor) {
                std::cout << "Unexpected number of duplicates received: " << (errorDetTable[key].window)[i] << ">" << splitFactor << endl;
            }
        }

    } else {
        errorDetTable[key] = ErrorDetectionWindow(sequenceWindowSize, seqNumber);
        (errorDetTable[key].window)[sequenceWindowSize-1]++;
    }
}

void LatentErrorDetection::finish() {
    for(unsigned int i = 0; i < sequenceWindowSize; i++) {
        for(auto it = errorDetTable.begin(); it != errorDetTable.end(); it++) {
            //emit(expectedPacketCount, splitFactor);
            emit(receivedDuplicates, ((it->second).window)[i]);
        }
    }
}

