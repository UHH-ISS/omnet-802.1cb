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

#ifndef SPB_PATHSELECTIONTABLE_H_
#define SPB_PATHSELECTIONTABLE_H_

#include <time.h>

#include "routing/ISISDefs.h"
#include "utils/L2Identifier.h"

typedef std::vector<ISISEthernetNodeMeta> Path;
typedef std::vector<Path> PathVector;

struct PathSelectionKey {
    L2Identifier key;
    MACAddress addr;

    PathSelectionKey() {};
    PathSelectionKey(L2Identifier key, MACAddress addr) {this->key = key; this->addr = addr;};

    bool operator<(const PathSelectionKey &psk ) const {
        return addr < psk.addr && key < psk.key ;
     };

    bool operator==(const PathSelectionKey &psk ) const {
        return addr == psk.addr && key == psk.key;
     };

    bool operator!=(const PathSelectionKey &psk ) const {
        return addr != psk.addr || key != psk.key;
     };

    void operator=(const PathSelectionKey &psk ) {
        key = psk.key;
        addr = psk.addr;
     };
};

struct PathIndicator {
    Path path;
    float stamp;
    bool is_enabled;

    PathIndicator(Path p, bool e) {path = p; is_enabled = e; stamp = time(0);};

    void updateStamp() {
        stamp = time(0);
    };

    bool isEnabled(float timeout) {
        return (time(0) - stamp) < timeout && is_enabled;
    };

    void setEnabled(bool e) {
        is_enabled = e;
    };

    Path getPath() {
        return path;
    };
};

typedef std::vector<PathIndicator> PathIndicatorVector;

class PathSelectionTable : public cSimpleModule {

public:
    double timeout;

    PathSelectionTable();
    virtual ~PathSelectionTable();

    std::map<PathSelectionKey, PathIndicatorVector> pathTable;

    PathVector getPathsForStream(L2Identifier, MACAddress);

    void updateTable(L2Identifier, MACAddress, PathVector);

    void updateTable(L2Identifier, MACAddress, Path);

    void deleteFromTable(L2Identifier, MACAddress);

    void deleteFromTable(L2Identifier, MACAddress, Path);

    void printTable();
    void printPath(Path);

protected:
    void initialize(int) override;
};

#endif /* SPB_PATHSELECTIONTABLE_H_ */
