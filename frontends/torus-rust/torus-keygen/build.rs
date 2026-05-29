fn main() {
    ::capnpc::CompilerCommand::new()
        // the file is just a symlink to the actual schema: this is only to have
        // a simpler output file than using ../../x/x/torus-protocol.capnp
        .file("capnp/torus-protocol.capnp")
        .run()
        .expect("compiling schema");
}
