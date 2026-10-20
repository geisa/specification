#!/bin/bash
jq=`which jq`
if [ -n "$jq" ]; then
	jq -c '.["geisa-application-manifest"].["manifest"]' < ../schemas/examples/vendor-application-manifest-example.json
else
	echo "jq not available in path"
fi
