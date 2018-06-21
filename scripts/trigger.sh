# https://docs.travis-ci.com/user/triggering-builds
# follow the following steps to generate API token:
# install ruby, check installation with "ruby -v"
# install travis: "gem install travis -v 1.8.8 --no-rdoc --no-ri"
# login with your Github credentials: "travis login"
# print your API token (this is to be kept secret!): "travis token"
# encrypt token and add it to .travis.yml: "travis encrypt TRAVIS_API_TOKEN=ygCWqiZ8fnZrTfH6veb9Xw --add" 
# now you are able to use TRAVIS_API_TOKEN in the build environment!

body='{
"request": {
"branch":"master"
}}'

curl -s -X POST \
   -H "Content-Type: application/json" \
   -H "Accept: application/json" \
   -H "Travis-API-Version: 3" \
   -H "Authorization: token $TRAVIS_API_TOKEN" \
   -d "$body" \
   https://api.travis-ci.org/repo/Infineon%2Fplatformio-infineonxmc/requests