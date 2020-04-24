#!/bin/bash
set -e
echo '+++ :evergreen_tree: Configuring Environment'
if [[ -z "$TIMEOUT" ]]; then # use defaults
    [[ -z "$BUILD_TIMEOUT" ]] && export BUILD_TIMEOUT='45'
    [[ -z "$TEST_TIMEOUT" ]] && export TEST_TIMEOUT='5'
else # user override
    [[ -z "$BUILD_TIMEOUT" ]] && export BUILD_TIMEOUT="$TIMEOUT"
    [[ -z "$TEST_TIMEOUT" ]] && export TEST_TIMEOUT="$TIMEOUT"
fi # the TIMEOUT=${TIMEOUT:-45} syntax does not work in the pipeline.yml for timeout values for some reason
echo '+++ :pipeline_upload: Deploying Pipeline Steps'
buildkite-agent pipeline upload .cicd/pipeline.yml