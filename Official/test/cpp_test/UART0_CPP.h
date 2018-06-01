
class Serial {
    unsigned long mask;
public:
    Serial(unsigned char port);

    unsigned char baudrate(unsigned int rate);
    unsigned char read();
    void write(unsigned char c);
    void write(unsigned char* str);
};
