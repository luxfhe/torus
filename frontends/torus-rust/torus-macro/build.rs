use std::path::PathBuf;

fn main() {
    let out_dir = PathBuf::from(std::env::var("OUT_DIR").unwrap());
    let target_dir = out_dir.join("../../../..").canonicalize().unwrap();
    let torus_dir = target_dir.join("torus");
    println!(
        "cargo:rustc-env=TORUS_BUILD_DIR={}",
        torus_dir.display()
    );
    #[cfg(target_os = "macos")]
    {
        println!("cargo::rustc-link-arg=-rpath");
        println!("cargo::rustc-link-arg={}", torus_dir.display());
    }
}
