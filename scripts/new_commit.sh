#!/bin/bash

## CONFIG
ROOT_PATH=.
VERSION_FILENAME=VERSION
DATE_FORMAT='%y.%m.%d'

# Read version file
$ROOT_PATH $VERSION_FILENAME

# Check if variables (major, minor, build type) exists.
if [ ! -n "$MAJOR" ] || [ ! -n "$MINOR" ] || [ ! -n "$BUILD_TYPE" ]; then
    echo "[ERROR] Check if MAJOR, MINOR and BUILD_TYPE have been defined!"
    exit 1
fi

# Prefix for commit comment - MAJOR.MINOR.BUILD_DATE-BUILD_TYPE, e.g. 0.1.19.04.01-dev
COMMIT_DESC_PREFIX="$MAJOR.$MINOR.$(date +$DATE_FORMAT)-$BUILD_TYPE"

# Read commit description and add new commit if correct
read -p "Commit description: " COMMIT_DESC
git add -A $ROOT_PATH && \
git status

echo "Commit comment: $COMMIT_DESC"
read -p "Commit and push to remote [yes/no]: " USER_ANSWER
if [ "$USER_ANSWER" == "yes" ]; then
    git commit -m "$COMMIT_DESC_PREFIX $COMMIT_DESC" && \
    git push origin master
else
    exit 1
fi
