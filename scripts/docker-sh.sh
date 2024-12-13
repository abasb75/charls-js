docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v "$(pwd)":/charls-js -w /charls-js \
  charljsbuild bash -login