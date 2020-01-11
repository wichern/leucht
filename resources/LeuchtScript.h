#ifndef __LEUCHT_RESOURCES_LEUCHTSCRIPT_H__
#define __LEUCHT_RESOURCES_LEUCHTSCRIPT_H__

namespace resource {

static const char* const LeuchtScript = R"SCRIPT(
function switch_state(id) {
    $('#errors').empty();
    $.ajax({
        url: 'api/app/activate/' + id,
        method: 'POST',
        dataType: 'text'
    }).done(function(data) {
         $('#apps').children('a').each(function() {
             $(this).removeClass("active");
         });
         $('#app_' + data).addClass("active");
    }).fail(function(jqXHR, textStatus) {
        $('#errors').append(`<div class="alert alert-danger" role="alert">${jqXHR.status}: ${jqXHR.responseText}</div>`);
    });
}

function button_pressed(direction) {
    $('#errors').empty();
    $.ajax({
        url: 'api/app/key/' + direction,
        method: 'POST',
        dataType: 'text'
    }).done(function(data) {
        // nothing
    }).fail(function(jqXHR, textStatus) {
        $('#errors').append(`<div class="alert alert-danger" role="alert">${jqXHR.status}: ${jqXHR.responseText}</div>`);
    });
}

$(document).ready(function() {
    // Get all apps.
    $.ajax({
        url: 'api/app/list',
        method: 'GET',
        dataType: 'json'
    }).done(function(data) {
        var id = 0;
        for (app of data) {
            $('#apps').append(`<a href="javascript:switch_state('${id}')" id="app_${id}" class="list-group-item list-group-item-action">${app}</a>`);
            id++;
        }
    }).fail(function(jqXHR, textStatus) {
        $('#errors').append(`<div class="alert alert-danger" role="alert">Failed to fetch apps: ${jqXHR.statusText}</div>`);
    });

    // Get active feature
    $.ajax({
        url: 'api/app/active',
        method: 'GET',
        dataType: 'text'
    }).done(function(data) {
        $('#app_' + data).addClass("active");
    }).fail(function(jqXHR, textStatus) {
        $('#errors').append(`<div class="alert alert-danger" role="alert">Failed to fetch active app: ${jqXHR.statusText}</div>`);
    });
});
)SCRIPT";

}  // namespace resource

#endif  // __LEUCHT_RESOURCES_LEUCHTSCRIPT_H__
