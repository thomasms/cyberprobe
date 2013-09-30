
/****************************************************************************

LI transport.

****************************************************************************/

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <deque>

#include <socket.h>

#include <boost/shared_ptr.hpp>

namespace etsi_li {

// A buffered transport.  Transmits PDUs, some PDUs are re-transmitted on
// reconnect.
class transport {

  private:

    // TCP socket.
    tcpip::tcp_socket sock;

    // True = the transport is connected.
    bool cnx;

    unsigned long cap_bytes;
    unsigned long cap_pdus;

    unsigned long cur_bytes;
    unsigned long cur_pdus;

    typedef std::vector<unsigned char> pdu;
    typedef boost::shared_ptr<pdu> pdu_ptr;

    std::deque<pdu_ptr> buffer;

  public:

    // Constructor.
    transport() { cnx = false; }

    // Destructor.
    virtual ~transport() { sock.close(); }

    // Returns boolean indicating whether the stream is connected.
    bool connected() { return cnx; }

    // Connect to host/port.  Also specifies the LIID for this transport.
    void connect(const std::string& host, int port) {

	// All exceptions left thrown.

	sock.connect(host, port);
	cnx = true;

	for(std::deque<pdu_ptr>::iterator it = buffer.begin();
	    it != buffer.end();
	    it++) {
	    
	    sock.write(**it);

	}

    }

    // Close the transport.
    void close() { sock.close(); cnx = false; }

    // Send a PDU.
    int write(pdu_ptr pdu) {

	buffer.push_back(pdu);
	cur_pdus++;
	cur_bytes += pdu->size();
	
	// If removing the front PDU would still leave plenty of stuff in
	// the buffer...
	while (!buffer.empty() && 
	       ((cur_bytes - buffer.front()->size()) > cap_bytes) &&
	       ((cur_pdus - 1) > cap_pdus)) {

	    // ...then delete that item.

	    cur_pdus--;
	    cur_bytes -= buffer.front()->size();
	    buffer.pop_front();
	    
	}

	// May except.
	int ret = sock.write(*pdu);

	if (ret < 0)
	    throw std::runtime_error("Didn't transmit PDU");
	
	if ((unsigned int)ret != pdu->size())
	    throw std::runtime_error("Didn't transmit PDU");

	return ret;
	
    }

    // Configure buffering.
    void set_buffer(unsigned long bytes, unsigned long pdus) {
	cap_bytes = bytes;
	cap_pdus = pdus;
    }

};

};

#endif
