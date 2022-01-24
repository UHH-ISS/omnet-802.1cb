//
// Generated file, do not edit! Created by nedtool 5.5 from routing/ISIS.msg.
//

#ifndef __ISIS_M_H
#define __ISIS_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "ISISDefs.h"
#include "inet/linklayer/ethernet/EtherFrame.h"
// }}

/**
 * Enum generated from <tt>routing/ISIS.msg:25</tt> by nedtool.
 * <pre>
 * enum ISISMsgType
 * {
 *     UPDATE = 0;
 *     HELLO = 1;
 *     HELLO_RESP = 2;
 *     DB_ANNOUNCE = 3;
 * }
 * </pre>
 */
enum ISISMsgType {
    UPDATE = 0,
    HELLO = 1,
    HELLO_RESP = 2,
    DB_ANNOUNCE = 3
};

/**
 * Class generated from <tt>routing/ISIS.msg:32</tt> by nedtool.
 * <pre>
 * packet ISISTimer
 * {
 *     int type \@enum(ISISMsgType);
 * }
 * </pre>
 */
class ISISTimer : public ::omnetpp::cPacket
{
  protected:
    int type;

  private:
    void copy(const ISISTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ISISTimer&);

  public:
    ISISTimer(const char *name=nullptr, short kind=0);
    ISISTimer(const ISISTimer& other);
    virtual ~ISISTimer();
    ISISTimer& operator=(const ISISTimer& other);
    virtual ISISTimer *dup() const override {return new ISISTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ISISTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ISISTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:36</tt> by nedtool.
 * <pre>
 * packet updateTimer extends ISISTimer
 * {
 *     type = ISISMsgType::UPDATE;
 * }
 * </pre>
 */
class updateTimer : public ::ISISTimer
{
  protected:

  private:
    void copy(const updateTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const updateTimer&);

  public:
    updateTimer(const char *name=nullptr, short kind=0);
    updateTimer(const updateTimer& other);
    virtual ~updateTimer();
    updateTimer& operator=(const updateTimer& other);
    virtual updateTimer *dup() const override {return new updateTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const updateTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, updateTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:40</tt> by nedtool.
 * <pre>
 * packet dbAnnounceTimer extends ISISTimer
 * {
 *     type = ISISMsgType::DB_ANNOUNCE;
 * }
 * </pre>
 */
class dbAnnounceTimer : public ::ISISTimer
{
  protected:

  private:
    void copy(const dbAnnounceTimer& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const dbAnnounceTimer&);

  public:
    dbAnnounceTimer(const char *name=nullptr, short kind=0);
    dbAnnounceTimer(const dbAnnounceTimer& other);
    virtual ~dbAnnounceTimer();
    dbAnnounceTimer& operator=(const dbAnnounceTimer& other);
    virtual dbAnnounceTimer *dup() const override {return new dbAnnounceTimer(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const dbAnnounceTimer& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, dbAnnounceTimer& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:44</tt> by nedtool.
 * <pre>
 * packet ISISPacket extends EthernetIIFrame
 * {
 *     int type \@enum(ISISMsgType);
 *     etherType = 0x88cc;
 *     ISISEthernetNodeMeta meta;
 * }
 * </pre>
 */
class ISISPacket : public ::EthernetIIFrame
{
  protected:
    int type;
    ISISEthernetNodeMeta meta;

  private:
    void copy(const ISISPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ISISPacket&);

  public:
    ISISPacket(const char *name=nullptr, short kind=0);
    ISISPacket(const ISISPacket& other);
    virtual ~ISISPacket();
    ISISPacket& operator=(const ISISPacket& other);
    virtual ISISPacket *dup() const override {return new ISISPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual ISISEthernetNodeMeta& getMeta();
    virtual const ISISEthernetNodeMeta& getMeta() const {return const_cast<ISISPacket*>(this)->getMeta();}
    virtual void setMeta(const ISISEthernetNodeMeta& meta);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ISISPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ISISPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:50</tt> by nedtool.
 * <pre>
 * packet helloPacket extends ISISPacket
 * {
 *     type = ISISMsgType::HELLO;
 * }
 * </pre>
 */
class helloPacket : public ::ISISPacket
{
  protected:

  private:
    void copy(const helloPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const helloPacket&);

  public:
    helloPacket(const char *name=nullptr, short kind=0);
    helloPacket(const helloPacket& other);
    virtual ~helloPacket();
    helloPacket& operator=(const helloPacket& other);
    virtual helloPacket *dup() const override {return new helloPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const helloPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, helloPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:54</tt> by nedtool.
 * <pre>
 * packet helloRespPacket extends ISISPacket
 * {
 *     type = ISISMsgType::HELLO_RESP;
 * }
 * </pre>
 */
class helloRespPacket : public ::ISISPacket
{
  protected:

  private:
    void copy(const helloRespPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const helloRespPacket&);

  public:
    helloRespPacket(const char *name=nullptr, short kind=0);
    helloRespPacket(const helloRespPacket& other);
    virtual ~helloRespPacket();
    helloRespPacket& operator=(const helloRespPacket& other);
    virtual helloRespPacket *dup() const override {return new helloRespPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const helloRespPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, helloRespPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>routing/ISIS.msg:58</tt> by nedtool.
 * <pre>
 * packet dbAnnouncePacket extends ISISPacket
 * {
 *     type = ISISMsgType::DB_ANNOUNCE;
 *     string dbSignature;
 *     ISISDatabase database;
 * }
 * </pre>
 */
class dbAnnouncePacket : public ::ISISPacket
{
  protected:
    ::omnetpp::opp_string dbSignature;
    ISISDatabase database;

  private:
    void copy(const dbAnnouncePacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const dbAnnouncePacket&);

  public:
    dbAnnouncePacket(const char *name=nullptr, short kind=0);
    dbAnnouncePacket(const dbAnnouncePacket& other);
    virtual ~dbAnnouncePacket();
    dbAnnouncePacket& operator=(const dbAnnouncePacket& other);
    virtual dbAnnouncePacket *dup() const override {return new dbAnnouncePacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getDbSignature() const;
    virtual void setDbSignature(const char * dbSignature);
    virtual ISISDatabase& getDatabase();
    virtual const ISISDatabase& getDatabase() const {return const_cast<dbAnnouncePacket*>(this)->getDatabase();}
    virtual void setDatabase(const ISISDatabase& database);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const dbAnnouncePacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, dbAnnouncePacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef __ISIS_M_H

