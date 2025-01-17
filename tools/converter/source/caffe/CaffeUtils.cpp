//
//  CaffeUtils.cpp
//  MNNConverter
//
//  Created by MNN on 2019/01/31.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#include "CaffeUtils.hpp"

#include <fstream>

bool read_proto_from_text(const char* filepath, google::protobuf::Message* message) {
    std::ifstream fs(filepath, std::ifstream::in);
    if (!fs.is_open()) {
        fprintf(stderr, "open failed %s\n", filepath);
        return false;
    }

    google::protobuf::io::IstreamInputStream input(&fs);
    bool success = google::protobuf::TextFormat::Parse(&input, message);

    fs.close();

    return success;
}

bool read_proto_from_binary(const char* filepath, google::protobuf::Message* message) {
    std::ifstream fs(filepath, std::ifstream::in | std::ifstream::binary);
    if (!fs.is_open()) {
        printf("open failed %s\n", filepath);
        return false;
    }
    google::protobuf::io::IstreamInputStream input(&fs);
    google::protobuf::io::CodedInputStream codedstr(&input);
    codedstr.SetTotalBytesLimit(512 * 1024 * 1024, 64 * 1024 * 1024);
    bool success = message->ParseFromCodedStream(&codedstr);
    fs.close();

    return success;
}
