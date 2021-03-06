#ifndef PACKETS_CLIENT_DISCON_SIG_H
#define PACKETS_CLIENT_DISCON_SIG_H

# include <packets/Packet.h>

# include <cstdint>

class ClientDisconSig : public Packet {
 public:
  ~ClientDisconSig() {}
  ClientDisconSig() {
    cmd_.header.magic_nb = kMagicNb;
    cmd_.header.code = kClientDisconSig;
  }

# pragma pack(push, 1)
  struct Body {
    int32_t client_id = 0;
  };

  struct Cmd {
    Packet::Header header;
    Body body;
  };
# pragma pack(pop)

  void set_id(int32_t client_id) {
    cmd_.body.client_id = client_id;
  }

  const char *pack() const {
    char *data = new char[sizeof(Cmd)];
    std::memcpy(data, &cmd_, sizeof(Cmd));
    return data;
  }

  static std::size_t body_size() { return sizeof(Body); }
  static Body unpack(const char *data) {
    Body body;
    std::memcpy(&body, data, sizeof(Body));
    return body;
  }

 private:
  Cmd cmd_;
};

#endif  // PACKETS_CLIENT_DISCON_SIG_H
