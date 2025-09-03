cd libs/minhook-master
git fetch --tags
latest=$(git describe --tags `git rev-list --tags --max-count=1`)
git checkout "$latest"
cd ../..
git add libs/minhook-master
git commit -m "Bump MinHook to $latest"