fn main() {
    cxx_build::bridge("src/torus-optimizer.rs")
        .std("c++17")
        .compile("torus-optimizer-bridge");

    println!("cargo:rustc-link-lib=static=torus-optimizer-bridge");
    println!("cargo:rerun-if-changed=src/");
}
